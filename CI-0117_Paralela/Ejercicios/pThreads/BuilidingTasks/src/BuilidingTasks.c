// Copyright [2025] Camila Rodríguez

#include "BuildingTasks.h"

// Estructura para representar un hilo y su función
typedef struct {
  pthread_t id; // Identificador del hilo
  void* (*trabajo)(void*); // Función a ejecutar por el hilo
  void* datos; // Datos compartidos entre hilos
} thread_t;

// Equipo de threads
typedef struct {
  size_t cantidad; // Cantidad de hilos creados
  size_t capacidad; // Capacidad máxima del equipo
  thread_t* threads; // Hilos
} equipo_threads; 

equipo_threads* reservarThreads(size_t capacidad, void* datos_compartidos) { // Reserva memoria para el equipo de threads
  equipo_threads* equipo = calloc(1, sizeof(equipo_threads)); // Reserva memoria para el equipo con calloc

  // Verifica si la reserva fue exitosa
  if (equipo) {
    equipo->threads = calloc(capacidad, sizeof(thread_t));
    equipo->capacidad = capacidad;
    for (size_t i = 0; i < capacidad; ++i)
      equipo->threads[i].datos = datos_compartidos;
  }

  return equipo;
}

int agregarThread(equipo_threads* equipo, void* (*trabajo)(void*)) { // Agrega un nuevo hilo al equipo

    // Verifica si hay espacio en el equipo
  if (equipo->cantidad < equipo->capacidad) {
    equipo->threads[equipo->cantidad].trabajo = trabajo;
    int error = pthread_create(&equipo->threads[equipo->cantidad].id,NULL, trabajo, equipo->threads[equipo->cantidad].datos); // Crea el hilo
    
    // Verifica si la creación del hilo fue exitosa
    if (!error)
      ++equipo->cantidad;
    return error;
  }
  return 1;
}

// Espera a que todos los hilos terminen su ejecución
void joinThreads(equipo_threads* equipo) {
  for (size_t i = 0; i < equipo->cantidad; ++i)
    pthread_join(equipo->threads[i].id, NULL);
  free(equipo->threads);
  free(equipo);
}

// Función para obtener los datos compartidos
void* getSharedData(void* datos) {
  return datos;
}

// Inicia las tareas de construcción
int iniciarTasks(semaforos* compartido) { 

  // Inicializa la semilla para la función usleep
  equipo_threads* equipo = reservarThreads(10, compartido);
  assert(equipo); // Verifica si la reserva fue exitosa (video Jeisson assert)

  // Inicializa los semáforos
  agregarThread(equipo, obraGris);
  agregarThread(equipo, plomeriaExterior);
  agregarThread(equipo, techo);
  agregarThread(equipo, pinturaExterior);
  agregarThread(equipo, plomeriaInterior);
  agregarThread(equipo, instalacionElectrica);
  agregarThread(equipo, acabadosExteriores);
  agregarThread(equipo, pinturaInterior);
  agregarThread(equipo, pisos);
  agregarThread(equipo, acabadosInteriores);

  joinThreads(equipo); // Espera a que todos los hilos terminen su ejecución y los une al main con .join
  return EXIT_SUCCESS;
}

// Implementación de las tareas de construcción
// Obra gris
void* obraGris(void* datos) {
  semaforos* compartido = (semaforos*)getSharedData(datos); // Obtiene los datos compartidos
  sem_wait(&compartido->semaforo1); // Espera a que el semáforo esté disponible
  
  puts("1.2 Obra gris inicia");
  usleep(lrand48() % compartido->duracion_maxima); // Simula el tiempo de ejecución de la tarea
  puts("1.2 Obra gris termina");

  // Libera los semáforos para las siguientes tareas
  sem_post(&compartido->semaforo2);
  sem_post(&compartido->semaforo3);
  return NULL;
} //Se repite para los demás procesos esta estructura, cambiando la tarea

// Plomería exterior
void* plomeriaExterior(void* datos) {
  semaforos* compartido = (semaforos*)getSharedData(datos);
  sem_wait(&compartido->semaforo2);
  puts("2.1 Plomería exterior inicia");
  usleep(lrand48() % compartido->duracion_maxima);
  puts("2.1 Plomería exterior termina");
  sem_post(&compartido->semaforo4);
  sem_post(&compartido->semaforo5);
  return NULL;
}

void* techo(void* datos) {
  semaforos* compartido = (semaforos*)getSharedData(datos);
  sem_wait(&compartido->semaforo3);
  puts("2.3 Techo inicia");
  usleep(lrand48() % compartido->duracion_maxima);
  puts("2.3 Techo termina");
  sem_post(&compartido->semaforo6);
  return NULL;
}

void* pinturaExterior(void* datos) {
  semaforos* compartido = (semaforos*)getSharedData(datos);
  sem_wait(&compartido->semaforo4);
  puts("3.1 Pintura exterior inicia");
  usleep(lrand48() % compartido->duracion_maxima);
  puts("3.1 Pintura exterior termina");
  sem_post(&compartido->semaforo7);
  return NULL;
}

void* plomeriaInterior(void* datos) {
  semaforos* compartido = (semaforos*)getSharedData(datos);
  sem_wait(&compartido->semaforo5);
  puts("3.2 Plomería interior inicia");
  usleep(lrand48() % compartido->duracion_maxima);
  puts("3.2 Plomería interior termina");
  sem_post(&compartido->semaforo8);
  return NULL;
}

void* instalacionElectrica(void* datos) {
  semaforos* compartido = (semaforos*)getSharedData(datos);
  sem_wait(&compartido->semaforo6);
  puts("3.3 Instalación eléctrica inicia");
  usleep(lrand48() % compartido->duracion_maxima);
  puts("3.3 Instalación eléctrica termina");
  sem_post(&compartido->semaforo11);
  return NULL;
}

void* acabadosExteriores(void* datos) {
  semaforos* compartido = (semaforos*)getSharedData(datos);
  sem_wait(&compartido->semaforo7);
  puts("4.1 Acabados exteriores inicia");
  usleep(lrand48() % compartido->duracion_maxima);
  puts("4.1 Acabados exteriores termina");
  return NULL;
}

void* pinturaInterior(void* datos) {
  semaforos* compartido = (semaforos*)getSharedData(datos);
  sem_wait(&compartido->semaforo8);
  sem_wait(&compartido->semaforo11);
  puts("4.3 Pintura interior inicia");
  usleep(lrand48() % compartido->duracion_maxima);
  puts("4.3 Pintura interior termina");
  sem_post(&compartido->semaforo9);
  return NULL;
}

void* pisos(void* datos) {
  semaforos* compartido = (semaforos*)getSharedData(datos);
  sem_wait(&compartido->semaforo9);
  puts("5.3 Pisos inicia");
  usleep(lrand48() % compartido->duracion_maxima);
  puts("5.3 Pisos termina");
  sem_post(&compartido->semaforo10);
  return NULL;
}

void* acabadosInteriores(void* datos) {
  semaforos* compartido = (semaforos*)getSharedData(datos);
  sem_wait(&compartido->semaforo10);
  puts("6.1 Acabados interiores inicia");
  usleep(lrand48() % compartido->duracion_maxima);
  puts("6.1 Acabados interiores termina");
  return NULL;
}

