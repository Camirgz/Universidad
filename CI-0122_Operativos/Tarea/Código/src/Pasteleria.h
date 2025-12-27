#ifndef PASTELERIA_H
#define PASTELERIA_H

#include "Platillo.h"
#include <semaphore.h>
#include <pthread.h>
#include <queue>
#include <vector>

class Pasteleria {
private:
    static const int NUM_HORNOS = 2;
    
    // Semáforos y mutex
    sem_t hornos_disponibles;
    pthread_mutex_t mutex_colas;
    pthread_mutex_t mutex_hornos;
    pthread_mutex_t mutex_cout;  // Para sincronizar salida a consola
    
    // Colas de espera
    std::queue<Platillo> cola_urgente;
    std::queue<Platillo> cola_normal;
    
    // Estado de hornos
    bool horno_ocupado[NUM_HORNOS];
    
    // Métodos privados
    int asignar_horno();
    void liberar_horno(int num_horno);
    Platillo obtener_siguiente_platillo();
    bool hay_platillos_esperando();
    void imprimir(const string& mensaje);
    
public:
    Pasteleria();
    ~Pasteleria();
    
    void agregar_a_cola(const Platillo& platillo);
    void hornear_platillo(int id_cocinero);
};

#endif