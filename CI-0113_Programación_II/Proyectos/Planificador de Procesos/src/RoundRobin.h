#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include "Algoritmo.h"
#include <iostream>

class RoundRobin : public Algoritmo { // Clase Algoritmo hereda a RoundRobin

// Atributos
private:
    /**
     * @brief  quantum del algoritmo, tiempo de ejecución de cada proceso
     * 
     */
    int quantum;

public:
    // Constructor
    /**
     * @brief Construct a new Round Robin object
     * 
     * @param quantum_  tiempo de ejecución de cada proceso
     */
    RoundRobin(int quantum_) : quantum(quantum_) {}

    // Método polimórfico
    /**
     * @brief metodo que ejecuta el algoritmo
     * 
     * @param cabeza 
     */
    void ejecutar(Proceso* cabeza) override;
    
};

#endif 
