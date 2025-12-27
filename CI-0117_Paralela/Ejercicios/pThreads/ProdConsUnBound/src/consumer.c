// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4

#include <stdbool.h>
#include <stdio.h>

#include "common.h"
#include "consumer.h"



void* consume(void* data) {
  // Convertir a estructura de simulación
  simulation_t* simulation = (simulation_t*)data;

  // Ciclo hasta consumir todo
  while (true) {
    // Lock para acceder a consumed_count
    pthread_mutex_lock(&simulation->can_access_consumed_count);
    
    // Si queda trabajo, reservar unidad
    if (simulation->consumed_count < simulation->unit_count) {
      ++simulation->consumed_count;
    } else {
      // Consumir, unlock y salir
      pthread_mutex_unlock(&simulation->can_access_consumed_count);
      break;
    }
    
    // Unlock después de reservar
    pthread_mutex_unlock(&simulation->can_access_consumed_count);

    // Esperar a que haya algo en la cola
    sem_wait(&simulation->can_consume);

    size_t value = 0;
    // Sacar unidad de la cola
    queue_dequeue(&simulation->queue, &value);
    printf("\tConsuming %zu\n", value);

    // Simular consumo con delay aleatorio
    usleep(1000 * random_between(simulation->consumer_min_delay
      , simulation->consumer_max_delay));
  }

  return NULL;
}
