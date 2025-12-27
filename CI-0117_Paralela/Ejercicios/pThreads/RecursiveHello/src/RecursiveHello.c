//Imports
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Declaramos la función 'greet' que será ejecutada por los hilos
void* greet(void* data);

int main(void) {
  pthread_t thread;  // Variable para almacenar el identificador del hilo principal
  size_t number = 5; // Número inicial que se pasará al hilo 

  // Intentamos crear un hilo y pasarle la dirección de 'number'
  int error = pthread_create(&thread, NULL, greet, &number);
  if (error == 0) {  
    pthread_join(thread, NULL);  //pthread_join: espera a que el hilo termine antes de continuar
  } else {
    
    fprintf(stderr, "Error: could not create secondary thread\n");
  }

  return 0;
}

// Función que será ejecutada por cada hilo creado
void* greet(void* data) {
  size_t number = *((size_t*)data);  // Convertimos el dato recibido a 'size_t'

  if (number == 0) {  // Si el número llega a 0, imprimimos un mensaje
    printf("Goodbye from secondary thread, number: %zu\n", number);
  } else {  // Si el número es mayor que 0, seguimos creando hilos recursivamente
    printf("No ultimo: %zu\n", number);  // Imprimir el número actual
    size_t next_number = number - 1;  

    pthread_t Secondthread;  // Variable para el identificador del segundo hilo
    pthread_create(&Secondthread, NULL, greet, &next_number);  // Creamos un segundo hilo
    pthread_join(Secondthread, NULL);  // Esperamos que el segundo hilo termine antes de continuar
  }

  return NULL;  
}
