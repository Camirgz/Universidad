// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0
#define _POSIX_C_SOURCE 200809L
#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Function prototype to avoid implicit declaration
void* generateRandomNumber(void* seed);

// thread_shared_data_t
typedef struct shared_data {
  uint64_t next_thread;
  uint64_t thread_count;
  uint64_t randomSecs;
} shared_data_t;

// thread_private_data_t
typedef struct private_data {
  uint64_t thread_number;  // rank
  shared_data_t* shared_data;
} private_data_t;

/**
 * @brief ...
 */
void* greet(void* data);
int create_threads(shared_data_t* shared_data);

// procedure main(argc, argv[])
int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  
  // Default thread count to the number of available processors
  uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);

  // Allocate shared data
  shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));
  if (!shared_data) {
    fprintf(stderr, "Error: could not allocate shared data\n");
    return 12;
  }

  // Parse thread count from command line if provided
  if (argc == 2) {
    if (sscanf(argv[1], "%" SCNu64, &thread_count) != 1) {
      fprintf(stderr, "Error: invalid thread count\n");
      free(shared_data);
      return 11;
    }
  }

  // Initialize random number generator
  unsigned int seed = time(NULL); 
  int random_number = *(int*)generateRandomNumber(&seed); // Generate random number
  if (random_number < 0) {
    fprintf(stderr, "Error: could not generate random number\n");
    free(shared_data);
    return 13;
  }

  
  shared_data->randomSecs = (uint64_t)random_number; // Assign the random number to randomSecs
  printf("RandomSecs: %" PRIu64 "\n", shared_data->randomSecs);
  // Initialize shared data
  shared_data->next_thread = 0;
  shared_data->thread_count = thread_count;

  struct timespec start_time, finish_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);

  error = create_threads(shared_data);

  clock_gettime(CLOCK_MONOTONIC, &finish_time);
  double elapsed_time = finish_time.tv_sec - start_time.tv_sec +
                        (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;

  printf("Execution time: %.9lfs\n", elapsed_time);

  free(shared_data);
  return error;
}  // end procedure

int create_threads(shared_data_t* shared_data) {
  int error = EXIT_SUCCESS;

  // Allocate memory for threads and private data
  pthread_t* threads = (pthread_t*)malloc(shared_data->thread_count * sizeof(pthread_t));
  private_data_t* private_data = (private_data_t*)calloc(shared_data->thread_count, sizeof(private_data_t));

  if (!threads || !private_data) {
    fprintf(stderr, "Error: could not allocate %" PRIu64 " threads\n", shared_data->thread_count);
    free(threads);
    free(private_data);
    return 22;
  }

  // Create threads
  for (uint64_t thread_number = 0; thread_number < shared_data->thread_count; ++thread_number) {
    private_data[thread_number].thread_number = thread_number;
    private_data[thread_number].shared_data = shared_data;

    error = pthread_create(&threads[thread_number], NULL, greet, &private_data[thread_number]);
    if (error != EXIT_SUCCESS) {
      fprintf(stderr, "Error: could not create secondary thread\n");
      error = 21;
      break;
    }
  }

  printf("Hello from main thread\n");

  // Wait for all threads to finish
  for (uint64_t thread_number = 0; thread_number < shared_data->thread_count; ++thread_number) {
    pthread_join(threads[thread_number], NULL);
  }

  free(private_data);
  free(threads);

  return error;
}

// procedure greet:
void* greet(void* data) {
  assert(data);
  private_data_t* private_data = (private_data_t*)data;
  shared_data_t* shared_data = private_data->shared_data;
  // Wait until it is my turn
  while (shared_data->next_thread < private_data->thread_number) {
    usleep(shared_data->randomSecs);
  }  // end while
  
  printf("Hello from secondary thread %" PRIu64 " of %" PRIu64 "\n",
         private_data->thread_number, shared_data->thread_count);

  // Allow subsequent thread to proceed
  ++shared_data->next_thread;

  return NULL;
}  // end procedure

// Function to generate a random number
void* generateRandomNumber(void* seed) {
  unsigned int* s = (unsigned int*)seed; // Cast seed to unsigned int
  int* number = (int*)malloc(sizeof(int)); // Allocate memory for the random number
  if (!number) {
    return NULL;
  }
  *number = rand_r(s) % 101; // Generate a random number between 0 and 100
  return number; // Return pointer to the allocated number
}
