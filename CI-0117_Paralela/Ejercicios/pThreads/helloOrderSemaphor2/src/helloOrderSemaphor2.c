// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0
#define _POSIX_C_SOURCE 199309L

#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Estructura compartida
typedef struct shared_data {
  sem_t* can_greet;
  uint64_t thread_count;
} shared_data_t;

// Estructura privada para cada hilo
typedef struct private_data {
  uint64_t thread_number;
  shared_data_t* shared_data;
} private_data_t;

void* greet(void* data);

int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);

  if (argc == 2) {
    if (sscanf(argv[1], "%" SCNu64, &thread_count) != 1) {
      fprintf(stderr, "Error: invalid thread count\n");
      return 11;
    }
  }

  shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));
  if (shared_data) {
    shared_data->can_greet = (sem_t*)calloc(thread_count, sizeof(sem_t));
    shared_data->thread_count = thread_count;

    for (uint64_t i = 0; i < thread_count; ++i) {
      error = sem_init(&shared_data->can_greet[i], 0, 0);
      if (error != 0) {
        fprintf(stderr, "Error: could not initialize semaphore %" PRIu64 "\n", i);
        return 22;
      }
    }

    pthread_t* threads = (pthread_t*)malloc(thread_count * sizeof(pthread_t));
    private_data_t* private_data = (private_data_t*)calloc(thread_count, sizeof(private_data_t));
    if (!threads || !private_data) {
      fprintf(stderr, "Error: could not allocate memory for threads\n");
      return 23;
    }

    struct timespec start_time, finish_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (uint64_t i = 0; i < thread_count; ++i) {
      private_data[i].thread_number = i;
      private_data[i].shared_data = shared_data;
      error = pthread_create(&threads[i], NULL, greet, &private_data[i]);
      if (error != 0) {
        fprintf(stderr, "Error: could not create thread %" PRIu64 "\n", i);
        return 21;
      }
    }

    // Mensaje del hilo principal
    printf("Hello from main thread\n");

    // Da permiso al hilo 0
    sem_post(&shared_data->can_greet[0]);

    // Esperar a que todos los hilos terminen
    for (uint64_t i = 0; i < thread_count; ++i) {
      pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &finish_time);
    double elapsed_time = finish_time.tv_sec - start_time.tv_sec +
      (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;
    printf("Execution time: %.9lfs\n", elapsed_time);

    for (uint64_t i = 0; i < thread_count; ++i) {
      sem_destroy(&shared_data->can_greet[i]);
    }

    free(threads);
    free(private_data);
    free(shared_data->can_greet);
    free(shared_data);
  } else {
    fprintf(stderr, "Error: could not allocate shared data\n");
    error = 12;
  }

  return error;
}

void* greet(void* data) {
  assert(data);
  private_data_t* private_data = (private_data_t*)data;
  shared_data_t* shared_data = private_data->shared_data;

  int error = sem_wait(&shared_data->can_greet[private_data->thread_number]);
  if (error != 0) {
    fprintf(stderr, "Error: could not wait for semaphore\n");
  }

  printf("Hello from secondary thread %" PRIu64 " of %" PRIu64 "\n",
         private_data->thread_number, shared_data->thread_count);

  uint64_t next = (private_data->thread_number + 1) % shared_data->thread_count;
  error = sem_post(&shared_data->can_greet[next]);
  if (error != 0) {
    fprintf(stderr, "Error: could not post to semaphore\n");
  }

  return NULL;
}
