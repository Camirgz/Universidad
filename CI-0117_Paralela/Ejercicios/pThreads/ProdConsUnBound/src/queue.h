#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>
#include <stdbool.h>


typedef struct queue_node {
  size_t data;               // Dato del nodo
  struct queue_node* next;   // Siguiente nodo
} queue_node_t;

typedef struct {
  pthread_mutex_t can_access_queue;  // Mutex de acceso
  queue_node_t* head;                // Inicio de la cola
  queue_node_t* tail;                // Final de la cola
} queue_t;

int queue_init(queue_t* queue);
int queue_destroy(queue_t* queue);
bool queue_is_empty(queue_t* queue);
int queue_enqueue(queue_t* queue, const size_t data);
int queue_dequeue(queue_t* queue, size_t* data);
void queue_clear(queue_t* queue);
void queue_remove_first_unsafe(queue_t* queue); 

#endif  // QUEUE_H
