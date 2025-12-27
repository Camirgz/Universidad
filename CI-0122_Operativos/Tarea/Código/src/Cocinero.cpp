#include "Cocinero.h"

Cocinero::Cocinero(int id_cocinero, const Platillo& plat, Pasteleria* past) {
    id = id_cocinero;
    platillo = plat;
    pasteleria = past;
}

void* Cocinero::thread_function(void* arg) {
    Cocinero* cocinero = (Cocinero*)arg;
    
    // Agregar platillo a la cola
    cocinero->pasteleria->agregar_a_cola(cocinero->platillo);
    
    // Hornear el platillo
    cocinero->pasteleria->hornear_platillo(cocinero->id);
    
    return NULL;
}

void Cocinero::iniciar() {
    pthread_create(&thread, NULL, thread_function, this);
}

void Cocinero::esperar() {
    pthread_join(thread, NULL);
}