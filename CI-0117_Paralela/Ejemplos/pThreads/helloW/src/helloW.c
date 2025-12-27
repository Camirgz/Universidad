// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0

//Includes
#include <assert.h>   // Verifica si una expresión es verdadera
#include <inttypes.h> // Permite trabajar con tipos de datos enteros portables como uint64_t
#include <pthread.h>  // Librería para manejar hilos en C
#include <stdint.h>   // Define tipos de datos enteros como uint64_t
#include <stdio.h>    // Entrada y salida estándar (printf, scanf)
#include <stdlib.h>   // Funciones estándar (malloc, free, exit, etc.)
#include <unistd.h>   // Funciones del sistema operativo (sysconf, etc.)


//Doxygen
/**
 * @brief ...
 */

// Definición de funciones
void* greet(void* data); //Función que saluda a los hilos
int create_threads(uint64_t thread_count); //Función que crea los hilos

int main(int argc, char* argv[]) { // argc: cantidad de argumentos, argv: arreglo de strings con los 

#if 0 //Desactivado temporalmente, si estuviera activo, imprimiría los argumentos ingresados
  for (int index = 0; index < argc; ++index) {
    printf("argv[%d] = '%s'\n", index, argv[index]);
  }
  return 0;
#endif

  int error = EXIT_SUCCESS; // Verifica si el programa termina bien
  // create thread_count as result of converting argv[1] to integer
  // thread_count := integer(argv[1])
  uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN); //thread count: obtiene el número de núcleos del procesador y lo usa como número de hilos predeterminado.
  if (argc == 2) { //si se ingreso un argumento
    if (sscanf(argv[1], "%" SCNu64, &thread_count) == 1) { //si se logra leer el argumento
    } else { //si no se logra leer el argumento
      fprintf(stderr, "Error: invalid thread count\n");
      return 11; // si no se logra detectar el argumento usa el 11
    }
  }

  error = create_threads(thread_count); //crea los hilos
  return error; // si todo salio bien es exit success
}  // end procedure


int create_threads(uint64_t thread_count) { //crea los hilos
  int error = EXIT_SUCCESS;
  // for thread_number := 0 to thread_count do
  pthread_t* threads = (pthread_t*) malloc(thread_count * sizeof(pthread_t)); //reserva memoria para los hilos
  if (threads) { //si se reservo memoria
    for (uint64_t thread_number = 0; thread_number < thread_count //crea los hilos
        ; ++thread_number) {
      // create_thread(greet, thread_number)
      error = pthread_create(&threads[thread_number], /*attr*/ NULL, greet //crea el hilo
        , /*arg*/ (void*) thread_number);
      if (error == EXIT_SUCCESS) { //si se logró crear el hilo
      } else {
        fprintf(stderr, "Error: could not create secondary thread\n");
        error = 21; //error al crear el hilo secundario 
        break;
      }
    }

    // print "Hello from main thread"
    printf("Hello from main thread\n");

    for (uint64_t thread_number = 0; thread_number < thread_count //espera a que los hilos terminen
        ; ++thread_number) {
      pthread_join(threads[thread_number], /*value_ptr*/ NULL); //espera a que el hilo termine y lo libera
    }

    free(threads); //libera la memoria
  } else {
    fprintf(stderr, "Error: could not allocate %" PRIu64 " threads\n"
      , thread_count);
    error = 22;
  }

  return error;
}

// procedure greet:
void* greet(void* data) {
  // assert(data);
  const uint64_t rank = (uint64_t) data;
  // print "Hello from secondary thread"
  printf("Hello from secondary thread %" PRIu64 "\n", rank);
  return NULL;
}  // end procedure