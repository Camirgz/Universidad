// Copyright 2021-2024 ECCI-UCR CC-BY 4.0
#define _DEFAULT_SOURCE

#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// my_random library ----------------------------------------------------------

// GCC values from https://en.wikipedia.org/wiki/Linear_congruential_generator
#define MODULUS 2147483648l
#define MULTIPLIER 1103515245l
#define INCREMENT 12345l

// Estructura para mantener el estado del generador
typedef struct {
  int actual;
} my_random_state_t;

// Variable global para compatibilidad con la interfaz original
__thread my_random_state_t my_state = {0};

void my_seed(int seed) {
  my_state.actual = seed;
}

int my_rand(int min, int max) {
  const long next = (MULTIPLIER * my_state.actual + INCREMENT) % MODULUS;
  my_state.actual = next;
  return min + next % (max - min);
}

// tester program -------------------------------------------------------------

int count = 0;
int* numbers = NULL;
int min = 0;
int max = 0;
size_t thread_count = 0;

void* generate(void* data);

int main(int argc, char* argv[]) {
  count = argc >= 2 ? atoi(argv[1]) : 1;
  min = argc >= 3 ? atoi(argv[2]) : 0;
  max = argc >= 4 ? atoi(argv[3]) : 100;
  const int seed = argc >= 5 ? atoi(argv[4]) : clock() % MODULUS;

  my_seed(seed);
  numbers = (int*) calloc(count, sizeof(int));
  assert(numbers);

  thread_count = sysconf(_SC_NPROCESSORS_ONLN);
  pthread_t threads[thread_count];
  for (size_t index = 0; index < thread_count; ++index) {
    pthread_create(&threads[index], NULL, generate, (void*)index);
  }

  for (size_t index = 0; index < thread_count; ++index) {
    pthread_join(threads[index], NULL);
  }

  for (int index = 0; index < count; ++index) {
    printf("%d\n", numbers[index]);
  }

  free(numbers);
  return EXIT_SUCCESS;
}

void* generate(void* data) {
  size_t rank = (size_t)data;
  // Usar la semilla global más offset único por thread
  int global_seed = my_state.actual; // Captura la semilla global
  my_seed(global_seed + rank * 7919 + 1);
  
  for (int index = rank; index < count; index += thread_count) {
    numbers[index] = my_rand(min, max);
  }
  return NULL;
}