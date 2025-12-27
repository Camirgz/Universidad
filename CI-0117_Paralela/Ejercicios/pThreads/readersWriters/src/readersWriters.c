#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>  // Para sleep()

sem_t can_access_medium;     // Para acceso exclusivo al recurso
sem_t can_access_reading;    // Para proteger reading_count
int reading_count = 0;       // Número de lectores activos

// Función de lectura simulada
void read_data() {
    printf("Leyendo...\n");
    sleep(1); // Simula el tiempo de lectura
}

// Función de escritura simulada
void write_data() {
    printf("Escribiendo...\n");
    sleep(1); // Simula el tiempo de escritura
}

// Función que ejecutan los lectores
void* reader(void* arg) {
    sem_wait(&can_access_reading);
    reading_count++;
    if (reading_count == 1) {
        sem_wait(&can_access_medium); // Primer lector bloquea a escritores
    }
    sem_post(&can_access_reading);

    // Sección crítica de lectura
    read_data();

    sem_wait(&can_access_reading);
    reading_count--;
    if (reading_count == 0) {
        sem_post(&can_access_medium); // Último lector libera a escritores
    }
    sem_post(&can_access_reading);
    return NULL;
}

// Función que ejecutan los escritores
void* writer(void* arg) {
    sem_wait(&can_access_medium);  // Acceso exclusivo
    write_data();
    sem_post(&can_access_medium);
    return NULL;
}

int main() {
    pthread_t threads[100];
    int index = 0;
    char command;

    sem_init(&can_access_medium, 0, 1);
    sem_init(&can_access_reading, 0, 1);

    printf("Ingrese 'R' para lector, 'W' para escritor, 'Q' para salir:\n");

    while (1) {
        scanf(" %c", &command);
        if (command == 'R') {
            pthread_create(&threads[index++], NULL, reader, NULL);
        } else if (command == 'W') {
            pthread_create(&threads[index++], NULL, writer, NULL);
        } else if (command == 'Q') {
            break;
        }
    }

    // Espera a que todos los hilos terminen
    for (int i = 0; i < index; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Limpieza
    sem_destroy(&can_access_medium);
    sem_destroy(&can_access_reading);

    return 0;
}
