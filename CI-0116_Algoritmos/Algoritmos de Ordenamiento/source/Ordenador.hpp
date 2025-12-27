#pragma once
#include <cstdint>
#include <string>

/*
Credits
Author: Prof. Arturo Camacho, Universidad de Costa Rica
 
Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
*/

class Ordenador {

    private:
    // Métodos privados auxiliares para algunos algoritmos de ordenamiento
    void merge(uint32_t *A, uint32_t l, uint32_t m, uint32_t r) const;
    void mergeSort(uint32_t *A, uint32_t l, uint32_t r) const;
    void heapify(uint32_t *arr, uint32_t n, uint32_t i) const;
    void quickSort(uint32_t *A, int low, int high) const;
    int particion(uint32_t *A, int low, int high) const;
    void countingSort(uint32_t *A, uint32_t n, uint32_t exp, uint32_t r) const; 
    void radixSort(uint32_t *A, uint32_t n) const;

    
    public:
    Ordenador() = default;
    ~Ordenador() = default;
   
    void ordenamientoPorSeleccion(uint32_t *A, uint32_t n) const;
    void ordenamientoPorInserccion(uint32_t *A, uint32_t n) const;
    void ordenamientoPorMezcla(uint32_t *A, uint32_t n) const;
    void ordenamientoPorMonticulos(uint32_t *A, uint32_t n) const;
    void ordenamientoRapido(uint32_t *A, uint32_t n) const;
    void ordenamientoPorResiduos(uint32_t *A, uint32_t n) const;

    constexpr const char* imprimirDatosDeTarea() const;
};