#ifndef COCINERO_H
#define COCINERO_H

#include "Platillo.h"
#include "Pasteleria.h"
#include <pthread.h>

class Cocinero {
private:
    int id;
    Platillo platillo;
    Pasteleria* pasteleria;
    pthread_t thread;
    
    static void* thread_function(void* arg);
    
public:
    Cocinero(int id_cocinero, const Platillo& plat, Pasteleria* past);
    void iniciar();
    void esperar();
};

#endif