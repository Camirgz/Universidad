#ifndef CONTROLADORARRAYS_HPP
#define CONTROLADORARRAYS_HPP

#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>

using namespace std;

class ControladorArrays{
    public:
        ControladorArrays() = default;
        ~ControladorArrays() = default;
        
        uint32_t* crearArray(uint32_t n);
        void destruirArray(uint32_t* A);
        void imprimirArray(uint32_t* A, uint32_t n);
        bool verificarOrden(uint32_t* A, uint32_t n);
        void Ejecutar();
        void GenerarPruebasAlgoritmo(uint32_t* mil, uint32_t* diezMil,
            uint32_t* cienMil, uint32_t* unMillon, string Algoritmo);
        void imprimirTiempo(const string& nombre, chrono::time_point<chrono::high_resolution_clock> inicio, chrono::time_point<chrono::high_resolution_clock> fin);
        uint32_t* copiarArray(uint32_t* original, uint32_t n);
};

#endif