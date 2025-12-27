#pragma once

#ifndef GENERAR_ARRAY_HPP      
#define GENERAR_ARRAY_HPP

#include <vector>              
#include <random>              // Para generar números aleatorios

using namespace std;           

class GenerarArray {         
public:
    GenerarArray() = default; // Constructor por defecto

    // Método que genera un vector con valores aleatorios entre 1 y n
    vector<int> generarRandom(size_t n = 1000000) {
        vector<int> arreglo(n);             // Crea un vector de tamaño n
        random_device seed;          // Fuente para semilla
        mt19937 generador(seed());  // Generador de números aleatorios
        uniform_int_distribution<> distribucion(1, static_cast<int>(n)); // Distribución uniforme entre 1 y n

        for (size_t i = 0; i < n; ++i) {
            arreglo[i] = distribucion(generador); // Asigna número aleatorio a cada posición
        }

        return arreglo; // Devuelve el vector generado
    }

    // Método que genera un vector ordenado del 1 al n
    vector<int> generarOrdenado(size_t n = 1000000) {
        vector<int> arreglo(n); // Crea un vector de tamaño n

        for (size_t i = 0; i < n; ++i) {
            arreglo[i] = static_cast<int>(i + 1); // Asigna valores crecientes desde 1 hasta n
        }

        return arreglo; // Devuelve el vector ordenado
    }
};

#endif
