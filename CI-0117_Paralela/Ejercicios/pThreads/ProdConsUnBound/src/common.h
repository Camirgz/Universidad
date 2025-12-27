// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4

#ifndef COMMON_H
#define COMMON_H

#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#include "queue.h"
#include <sys/types.h>


typedef struct simulation {
  size_t unit_count;                    // Total de unidades
  size_t producer_count;               // Cantidad de productores
  size_t consumer_count;               // Cantidad de consumidores
  int producer_min_delay;             // Retraso mínimo productor
  int producer_max_delay;             // Retraso máximo productor
  int consumer_min_delay;             // Retraso mínimo consumidor
  int consumer_max_delay;             // Retraso máximo consumidor

  queue_t queue;                       // Cola compartida
  pthread_mutex_t can_access_next_unit; // Mutex para next_unit
  size_t next_unit;                   // Siguiente unidad a producir
  sem_t can_consume;                  // Semáforo para consumir
  pthread_mutex_t can_access_consumed_count; // Mutex para consumed_count
  size_t consumed_count;              // Unidades consumidas
} simulation_t;


int random_between(int min, int max);

#endif  // COMMON_H
