// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0

#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// thread_private_data_t
typedef struct private_data { //Estructura de datos para los hilos
  uint64_t thread_number;  // rank
  uint64_t thread_count;
  struct private_data* next;
} private_data_t;

/**
 * @brief ...
 */
void* greet(void* data);
int create_threads(uint64_t thread_count);

// procedure main(argc, argv[])
int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  // create thread_count as result of converting argv[1] to integer
  // thread_count := integer(argv[1])
  uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);
  if (argc == 2) {
    if (sscanf(argv[1], "%" SCNu64, &thread_count) == 1) {
    } else {
      fprintf(stderr, "Error: invalid thread count\n");
      return 11;
    }
  }

  error = create_threads(thread_count);
  return error;
}  // end procedure


int create_threads(uint64_t thread_count) {
  int error = EXIT_SUCCESS;
  // for thread_number := 0 to thread_count do
  pthread_t* threads = (pthread_t*) malloc(thread_count * sizeof(pthread_t)); //Crear los espacios en memoria para los hilos
  private_data_t* private_data = (private_data_t*) //puntero a private data t (estructura es parecido a un objeto, no tiene metodos), se tienen que inicializar en memoria tambié
    calloc(thread_count, sizeof(private_data_t)); //malloc: los valores de la memoria no se inicializan, calloc: los valores de la memoria se inicializan a 0

  if (threads && private_data) {

    for (uint64_t thread_number = 0; thread_number < thread_count
        ; ++thread_number) {
      private_data[thread_number].thread_number = thread_number; //Inicializar los valores de la estructura
      private_data[thread_number].thread_count = thread_count; //Inicializar los valores de la estructura

      // create_thread(greet, thread_number)
      error = pthread_create(&threads[thread_number], /*attr*/ NULL, greet //Crear el hilo con la función greet y el puntero a la estructura private_data
        , /*arg*/ &private_data[thread_number]); //Pasar la estructura como argumento a la función greet
      if (error == EXIT_SUCCESS) { //Si el hilo se creó correctamente
      } else {
        fprintf(stderr, "Error: could not create secondary thread\n");
        error = 21;
        break;
      }
    }

    // print "Hello from main thread"
    printf("Hello from main thread\n");

    for (uint64_t thread_number = 0; thread_number < thread_count
        ; ++thread_number) {
      pthread_join(threads[thread_number], /*value_ptr*/ NULL); //Esperar a que el hilo termine
    }

    // free memory
    free(private_data);
    free(threads);
  } else {
    fprintf(stderr, "Error: could not allocate %" PRIu64 " threads\n"
      , thread_count);
    error = 22;
  }

  return error;
}

// procedure greet:
void* greet(void* data) { //siempre tiene que recibir un puntero a void y devolver un puntero a void
  private_data_t* private_data = (private_data_t*) data; //Castear el puntero a void a un puntero a private_data_t
  // print "Hello from secondary thread"
  printf("Hello from secondary thread %" PRIu64 " of %" PRIu64 "\n"
    , (*private_data).thread_number, private_data->thread_count); //Imprimir el número del hilo y el número total de hilos
  return NULL;
}  // end procedure
