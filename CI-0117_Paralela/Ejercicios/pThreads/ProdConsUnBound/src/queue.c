// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4

#include <assert.h>
#include <stdlib.h>

#include "queue.h"

int queue_init(queue_t* queue) {
  assert(queue); // Verifica que no sea NULL
  int error = pthread_mutex_init(&queue->can_access_queue, NULL); // Init mutex
  queue->head = NULL;  // Init cabeza
  queue->tail = NULL;  // Init cola
  return error;
}

int queue_destroy(queue_t* queue) {
  queue_clear(queue); // Vacía la cola
  return pthread_mutex_destroy(&queue->can_access_queue); // Destruye mutex
}

bool queue_is_empty(queue_t* queue) {
  assert(queue); // Verifica que no sea NULL
  pthread_mutex_lock(&queue->can_access_queue); // Lock cola
  bool result = queue->head == NULL; // ¿Está vacía?
  pthread_mutex_unlock(&queue->can_access_queue); // Unlock cola
  return result;
}

bool queue_is_empty_unsafe(queue_t* queue) {
  assert(queue); // Verifica que no sea NULL
  return queue->head == NULL; // ¿Vacía sin lock?
}

int queue_enqueue(queue_t* queue, const size_t data) {
  assert(queue); // Verifica que no sea NULL
  int error = EXIT_SUCCESS;

  queue_node_t* new_node = (queue_node_t*) calloc(1, sizeof(queue_node_t)); // Nuevo nodo
  if (new_node) {
    new_node->data = data; // Asigna datos

    pthread_mutex_lock(&queue->can_access_queue); // Lock cola
    if (queue->tail) {
      queue->tail = queue->tail->next = new_node; // Añadir al final
    } else {
      queue->head = queue->tail = new_node; // Primer nodo
    }
    pthread_mutex_unlock(&queue->can_access_queue); // Unlock cola
  } else {
    error = EXIT_FAILURE; // Fallo de memoria
  }

  return error;
}

int queue_dequeue(queue_t* queue, size_t* data) {
  assert(queue); // Verifica que no sea NULL
  int error = 0;

  pthread_mutex_lock(&queue->can_access_queue); // Lock cola
  if (!queue_is_empty_unsafe(queue)) {
    if (data) {
      *data = queue->head->data; // Obtener datos
    }
    queue_remove_first_unsafe(queue); // Eliminar nodo
  } else {
    error = EXIT_FAILURE; // Cola vacía
  }
  pthread_mutex_unlock(&queue->can_access_queue); // Unlock cola

  return error;
}

void queue_remove_first_unsafe(queue_t* queue) {
  assert(queue); // Verifica que no sea NULL
  assert(!queue_is_empty_unsafe(queue)); // No debe estar vacía
  queue_node_t* node = queue->head; // Primer nodo
  queue->head = queue->head->next; // Mover cabeza
  free(node); // Liberar nodo
  if (queue->head == NULL) {
    queue->tail = NULL; // Ajustar tail si está vacía
  }
}

void queue_clear(queue_t* queue) {
  assert(queue); // Verifica que no sea NULL
  pthread_mutex_lock(&queue->can_access_queue); // Lock cola
  while (!queue_is_empty_unsafe(queue)) { // Vaciar nodos
    queue_remove_first_unsafe(queue);
  }
  pthread_mutex_unlock(&queue->can_access_queue); // Unlock cola
}
