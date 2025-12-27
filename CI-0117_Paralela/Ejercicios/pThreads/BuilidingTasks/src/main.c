// Copyright [2025] Camila Rodríguez
# include "BuildingTasks.h"

int main(void) {

    srand48(time(NULL)); // Inicializa la semilla para la función usleep
    semaforos compartido; // Estructura para los semáforos
  
    compartido.duracion_maxima = 2000000; // 2 segundos máximo por tarea
  
    // Inicializa los semáforos
    sem_init(&compartido.semaforo1, 0, 1);  // Obra gris empieza sola
    sem_init(&compartido.semaforo2, 0, 0);  // Espera obra gris
    sem_init(&compartido.semaforo3, 0, 0);  // Espera obra gris
    sem_init(&compartido.semaforo4, 0, 0);  // Espera plomería exterior
    sem_init(&compartido.semaforo5, 0, 0);  // Espera plomería exterior
    sem_init(&compartido.semaforo6, 0, 0);  // Espera techo
    sem_init(&compartido.semaforo7, 0, 0);  // Espera pintura exterior
    sem_init(&compartido.semaforo8, 0, 0);  // Espera plomería interior
    sem_init(&compartido.semaforo9, 0, 0);  // Espera pintura interior
    sem_init(&compartido.semaforo10, 0, 0); // Espera pisos
    sem_init(&compartido.semaforo11, 0, 0); // Espera instalación eléctrica
  
    // Inicia las tareas
    iniciarTasks(&compartido);
  
    // Espera a que todas las tareas terminen y libera los semáforos 
    sem_destroy(&compartido.semaforo1);
    sem_destroy(&compartido.semaforo2);
    sem_destroy(&compartido.semaforo3);
    sem_destroy(&compartido.semaforo4);
    sem_destroy(&compartido.semaforo5);
    sem_destroy(&compartido.semaforo6);
    sem_destroy(&compartido.semaforo7);
    sem_destroy(&compartido.semaforo8);
    sem_destroy(&compartido.semaforo9);
    sem_destroy(&compartido.semaforo10);
    sem_destroy(&compartido.semaforo11);
  
    return EXIT_SUCCESS;
  }
  