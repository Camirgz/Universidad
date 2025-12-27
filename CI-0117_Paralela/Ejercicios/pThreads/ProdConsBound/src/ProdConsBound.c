// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
// Simula un productor y un consumidor que comparten un buffer con capacidad limitada

/**
 * @file prod_cons_bound.c
 * @brief Ejemplo comentado que simula la producción y consumo con buffer acotado.
 */

// @see `man feature_test_macros`
/**
 * @brief Macro para habilitar características específicas de compilación.
 */
#define _DEFAULT_SOURCE

#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include <unistd.h>

/**
 * @brief Enumeración de errores posibles durante la ejecución.
 */
enum {
  ERR_NOMEM_SHARED = EXIT_FAILURE + 1,
  ERR_NOMEM_BUFFER,
  ERR_NO_ARGS,
  ERR_BUFFER_CAPACITY,
  ERR_ROUND_COUNT,
  ERR_MIN_PROD_DELAY,
  ERR_MAX_PROD_DELAY,
  ERR_MIN_CONS_DELAY,
  ERR_MAX_CONS_DELAY,
  ERR_CREATE_THREAD,
};

/**
 * @brief Estructura para almacenar información compartida entre hilos.
 */
typedef struct {
  size_t thread_count;     /**< Número total de hilos */
  size_t buffer_capacity;  /**< Tamaño del buffer */
  double *buffer;          /**< Arreglo que representa el buffer */
  size_t rounds;           /**< Cantidad de rondas de producción/consumo */
  useconds_t producer_min_delay; /**< Retardo mínimo del productor */
  useconds_t producer_max_delay; /**< Retardo máximo del productor */
  useconds_t consumer_min_delay; /**< Retardo mínimo del consumidor */
  useconds_t consumer_max_delay; /**< Retardo máximo del consumidor */

  sem_t can_produce; /**< Semáforo que indica si se puede producir */
  sem_t can_consume; /**< Semáforo que indica si se puede consumir */
} shared_data_t;

/**
 * @brief Información específica para cada hilo (no se usa en este ejemplo).
 */
typedef struct {
  size_t thread_number;       /**< Número identificador del hilo */
  shared_data_t *shared_data; /**< Apuntador a los datos compartidos */
} private_data_t;

// Declaración de funciones
int analyze_arguments(int argc, char *argv[], shared_data_t *shared_data);
int create_threads(shared_data_t *shared_data);
void *produce(void *data);
void *consume(void *data);
useconds_t random_between(useconds_t min, useconds_t max);

int main(int argc, char *argv[]) {
  int error = EXIT_SUCCESS;

  // Reservamos memoria para la estructura compartida
  shared_data_t *shared_data = (shared_data_t *)calloc(1, sizeof(shared_data_t));

  if (shared_data) {
    // Validamos los argumentos pasados por línea de comandos
    error = analyze_arguments(argc, argv, shared_data);

    if (error == EXIT_SUCCESS) {
      // Reservamos memoria para el buffer de datos
      shared_data->buffer =
          (double *)calloc(shared_data->buffer_capacity, sizeof(double));

      if (shared_data->buffer) {
        // Inicializamos los semáforos
        sem_init(&shared_data->can_produce, 0, shared_data->buffer_capacity);
        sem_init(&shared_data->can_consume, 0, 0);  // al inicio no se puede consumir

        unsigned int seed = 0u;
        // Obtenemos una semilla aleatoria del sistema operativo
        getrandom(&seed, sizeof(seed), GRND_NONBLOCK);
        srandom(seed); // Inicializamos el generador de números pseudoaleatorios

        // Medimos el tiempo de ejecución
        struct timespec start_time;
        clock_gettime(CLOCK_MONOTONIC, &start_time);

        // Creamos los hilos productor y consumidor
        error = create_threads(shared_data);

        struct timespec finish_time;
        clock_gettime(CLOCK_MONOTONIC, &finish_time);

        double elapsed = (finish_time.tv_sec - start_time.tv_sec) +
                         (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;
        printf("execution time: %.9lfs\n", elapsed);

        // Destruimos los semáforos y liberamos memoria
        sem_destroy(&shared_data->can_produce);
        sem_destroy(&shared_data->can_consume);
        free(shared_data->buffer);
      } else {
        fprintf(stderr, "error: could not create buffer\n");
        error = ERR_NOMEM_BUFFER;
      }
    }

    free(shared_data);
  } else {
    fprintf(stderr, "Error: could not allocate shared data\n");
    error = ERR_NOMEM_SHARED;
  }

  return error;
}

int analyze_arguments(int argc, char *argv[], shared_data_t *shared_data) {
  int error = EXIT_SUCCESS;

  if (argc == 7) {
    // Extraemos los valores numéricos desde la línea de comandos
    if (sscanf(argv[1], "%zu", &shared_data->buffer_capacity) != 1 ||
        shared_data->buffer_capacity == 0) {
      fprintf(stderr, "error: invalid buffer capacity\n");
      error = ERR_BUFFER_CAPACITY;
    } else if (sscanf(argv[2], "%zu", &shared_data->rounds) != 1 ||
               shared_data->rounds == 0) {
      fprintf(stderr, "error: invalid round count\n");
      error = ERR_ROUND_COUNT;
    } else if (sscanf(argv[3], "%u", &shared_data->producer_min_delay) != 1) {
      fprintf(stderr, "error: invalid min producer delay\n");
      error = ERR_MIN_PROD_DELAY;
    } else if (sscanf(argv[4], "%u", &shared_data->producer_max_delay) != 1) {
      fprintf(stderr, "error: invalid max producer delay\n");
      error = ERR_MAX_PROD_DELAY;
    } else if (sscanf(argv[5], "%u", &shared_data->consumer_min_delay) != 1) {
      fprintf(stderr, "error: invalid min consumer delay\n");
      error = ERR_MIN_CONS_DELAY;
    } else if (sscanf(argv[6], "%u", &shared_data->consumer_max_delay) != 1) {
      fprintf(stderr, "error: invalid max consumer delay\n");
      error = ERR_MAX_CONS_DELAY;
    }
  } else {
    fprintf(stderr, "usage: prod_cons_bound buffer_capacity rounds"
                    " producer_min_delay producer_max_delay"
                    " consumer_min_delay consumer_max_delay\n");
    error = ERR_NO_ARGS;
  }

  return error;
}

int create_threads(shared_data_t *shared_data) {
  assert(shared_data);
  int error = EXIT_SUCCESS;

  pthread_t producer, consumer;

  // Creamos el hilo productor
  error = pthread_create(&producer, NULL, produce, shared_data);
  if (error == EXIT_SUCCESS) {
    // Creamos el hilo consumidor
    error = pthread_create(&consumer, NULL, consume, shared_data);
    if (error != EXIT_SUCCESS) {
      fprintf(stderr, "error: could not create consumer\n");
      error = ERR_CREATE_THREAD;
    }
  } else {
    fprintf(stderr, "error: could not create producer\n");
    error = ERR_CREATE_THREAD;
  }

  if (error == EXIT_SUCCESS) {
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);
  }

  return error;
}

void *produce(void *data) {
  shared_data_t *shared_data = (shared_data_t *)data;
  size_t count = 0;

  for (size_t round = 0; round < shared_data->rounds; ++round) {
    for (size_t index = 0; index < shared_data->buffer_capacity; ++index) {
      // Esperar permiso para producir
      sem_wait(&shared_data->can_produce);

      // Simulamos un retardo
      usleep(1000 * random_between(shared_data->producer_min_delay,
                                   shared_data->producer_max_delay));

      // Guardamos el nuevo dato en el buffer
      shared_data->buffer[index] = ++count;

      printf("Produced %lg\n", shared_data->buffer[index]);

      // Señalizamos que hay algo disponible para consumir
      sem_post(&shared_data->can_consume);
    }
  }

  return NULL;
}

void *consume(void *data) {
  shared_data_t *shared_data = (shared_data_t *)data;

  for (size_t round = 0; round < shared_data->rounds; ++round) {
    for (size_t index = 0; index < shared_data->buffer_capacity; ++index) {
      // Esperar permiso para consumir
      sem_wait(&shared_data->can_consume);

      // Simulamos un retardo
      usleep(1000 * random_between(shared_data->consumer_min_delay,
                                   shared_data->consumer_max_delay));

      printf("Consumed %lg\n", shared_data->buffer[index]);

      // Indicamos que hay espacio para producir
      sem_post(&shared_data->can_produce);
    }
  }

  return NULL;
}

useconds_t random_between(useconds_t min, useconds_t max) {
  return min + random() % (max - min + 1);
}
