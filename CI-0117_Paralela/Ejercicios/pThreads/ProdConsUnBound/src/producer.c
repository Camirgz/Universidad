// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4

#include <stdio.h>

#include "common.h"
#include "producer.h"

void* produce(void* data) {
  simulation_t* simulation = (simulation_t*)data;

  // Ciclo hasta producir todo
  while (true) {
    size_t my_unit = 0;

    // Lock para next_unit
    pthread_mutex_lock(&simulation->can_access_next_unit);

    // Si hay trabajo, tomar unidad
    if (simulation->next_unit < simulation->unit_count) {
      my_unit = ++simulation->next_unit;
    } else {
      // Nada más que producir, unlock y salir
      pthread_mutex_unlock(&simulation->can_access_next_unit);
      break;
    }

    // Unlock después de tomar unidad
    pthread_mutex_unlock(&simulation->can_access_next_unit);

    // Simular producción con delay aleatorio
    usleep(1000 * random_between(simulation->producer_min_delay
      , simulation->producer_max_delay));

    // Encolar unidad producida
    queue_enqueue(&simulation->queue, my_unit);
    printf("Produced %zu\n", my_unit);

    // Señal para consumidores
    sem_post(&simulation->can_consume);
  }

  return NULL;
}
