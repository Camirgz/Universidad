// Copyright [2025] Camila Rodríguez

#ifndef BUILDINGTASKS_H
#define BUILDINGTASKS_H

// includes 
#define _XOPEN_SOURCE 500 // Para usar usleep
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

// Estructura de datos compartidos con todos los semáforos
typedef struct shared_data {
    useconds_t duracion_maxima;
    sem_t semaforo1;
    sem_t semaforo2;
    sem_t semaforo3;
    sem_t semaforo4;
    sem_t semaforo5;
    sem_t semaforo6;
    sem_t semaforo7;
    sem_t semaforo8;
    sem_t semaforo9;
    sem_t semaforo10;
    sem_t semaforo11;
} semaforos;

// Funciones de tareas
int iniciarTasks(semaforos* compartido);
void* obraGris(void* datos);
void* plomeriaExterior(void* datos);
void* techo(void* datos);
void* pinturaExterior(void* datos);
void* plomeriaInterior(void* datos);
void* instalacionElectrica(void* datos);
void* acabadosExteriores(void* datos);
void* pinturaInterior(void* datos);
void* pisos(void* datos);
void* acabadosInteriores(void* datos);

#endif
