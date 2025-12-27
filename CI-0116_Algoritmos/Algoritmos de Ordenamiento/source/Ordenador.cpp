#include "Ordenador.hpp"
#include "ControladorArrays.hpp"
#include <iostream>
#include <chrono>
#include <cmath>
using namespace std;
using namespace std::chrono;

ControladorArrays arrays;

void Ordenador::ordenamientoPorSeleccion(uint32_t *A, uint32_t n) const {
    arrays.verificarOrden(A, n);
    auto inicio = high_resolution_clock::now();

    for (uint32_t i = 0; i < n - 1; ++i) {
        uint32_t minIndex = i;
        for (uint32_t j = i + 1; j < n; ++j) {
            if (A[j] < A[minIndex])
                minIndex = j;
        }
        swap(A[i], A[minIndex]);
    }

    auto fin = high_resolution_clock::now();
    arrays.verificarOrden(A, n);
    arrays.imprimirTiempo("seleccion", inicio, fin);
}

void Ordenador::ordenamientoPorInserccion(uint32_t *A, uint32_t n) const {
    arrays.verificarOrden(A, n);
    auto inicio = high_resolution_clock::now();

    for (uint32_t i = 1; i < n; ++i) {
        uint32_t key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            --j;
        }
        A[j + 1] = key;
    }

    auto fin = high_resolution_clock::now();
    arrays.verificarOrden(A, n);
    arrays.imprimirTiempo("insercion", inicio, fin);
}

void Ordenador::ordenamientoPorMezcla(uint32_t *A, uint32_t n) const {
    arrays.verificarOrden(A, n);

    auto inicio = high_resolution_clock::now();
    mergeSort(A, 0, n - 1); // Llamar a la función de ordenamiento por mezcla recursiva
    auto fin = high_resolution_clock::now();

    arrays.verificarOrden(A, n);
    arrays.imprimirTiempo("mezcla", inicio, fin);
}

void Ordenador::mergeSort(uint32_t *A, uint32_t l, uint32_t r) const {

    // Caso base
    if (l < r) {
        // Encontrar el punto medio
        uint32_t m = l + (r - l) / 2;
        // Ordenar la primera y segunda mitad
        mergeSort(A, l, m);
        mergeSort(A, m + 1, r);
        // Mezclar las mitades ordenadas
        merge(A, l, m, r);
    }
}

void Ordenador::merge(uint32_t *A, uint32_t l, uint32_t m, uint32_t r) const {
    // Crear vars temporales
    uint32_t n1 = m - l + 1;
    uint32_t n2 = r - m;

    // Crear arrays temporales
    uint32_t *L = new uint32_t[n1];
    uint32_t *R = new uint32_t[n2];

    // Copiar datos a los arrays temporales
    for (uint32_t i = 0; i < n1; ++i)
        L[i] = A[l + i];
    for (uint32_t j = 0; j < n2; ++j)
        R[j] = A[m + 1 + j];

    uint32_t i = 0, j = 0, k = l;

    // Mezclar los arrays temporales
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k++] = L[i++];
        } else {
            A[k++] = R[j++];
        }
    }

    // Copiar los elementos restantes de L[] si hay alguno
    while (i < n1) A[k++] = L[i++];
    // Copiar los elementos restantes de R[] si hay alguno
    while (j < n2) A[k++] = R[j++];

    // Liberar memoria
    delete[] L;
    delete[] R;
}

void Ordenador::ordenamientoPorMonticulos(uint32_t *A, uint32_t n) const {
    arrays.verificarOrden(A, n);
    auto inicio = high_resolution_clock::now();

    // Construir el heap (reorganizar el arreglo)
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(A, n, i);
    }

    // Extraer uno por uno los elementos del heap
    for (int i = n - 1; i > 0; --i) {
        // Mover la raíz actual al final
        swap(A[0], A[i]);

        // Llamar a heapify en el heap reducido
        heapify(A, i, 0);
    }

    auto fin = high_resolution_clock::now();
    arrays.verificarOrden(A, n);
    arrays.imprimirTiempo("monticulos", inicio, fin);
}

void Ordenador::heapify(uint32_t *arr, uint32_t n, uint32_t i) const {
    uint32_t mayor = i;
    uint32_t left = 2 * i + 1;
    uint32_t right = 2 * i + 2;

    // Si el hijo izquierdo es mayor que la raíz
    if (left < n && arr[left] > arr[mayor])
        mayor = left; // Cambiar mayor si el hijo izquierdo es mayor
    
    // Si el hijo derecho es mayor que el mayor hasta ahora
    if (right < n && arr[right] > arr[mayor])
        mayor = right; // Cambiar mayor si el hijo derecho es mayor

    // Si el mayor no es la raíz
    if (mayor != i) {
        swap(arr[i], arr[mayor]); // Intercambiar la raíz con el mayor
        heapify(arr, n, mayor); // Recursivamente heapificar el subárbol afectado
    }
}

void Ordenador::ordenamientoRapido(uint32_t *A, uint32_t n) const {
    arrays.verificarOrden(A, n);
    auto inicio = high_resolution_clock::now();

    quickSort(A, 0, n - 1); // Llamada al método quicksort recursivo

    auto fin = high_resolution_clock::now();
    arrays.verificarOrden(A, n);
    arrays.imprimirTiempo("quicksort", inicio, fin);
}

void Ordenador::quickSort(uint32_t *A, int low, int high) const {

    // Caso base
    if (low < high) {
        int pi = particion(A, low, high); // Índice de partición 

        quickSort(A, low, pi - 1);  // Ordenar los elementos antes de la partición
        quickSort(A, pi + 1, high); // Ordenar los elementos después de la partición
    }
}

int Ordenador::particion(uint32_t *A, int low, int high) const {
    uint32_t pivote = A[high]; // Escoger el último elemento como pivote
    int i = low - 1;          // Índice del elemento menor

    // Reorganizar el arreglo
    for (int j = low; j < high; ++j) {
        if (A[j] < pivote) {
            ++i;
            swap(A[i], A[j]);
        }
    }
    // Intercambiar el pivote con el elemento en la posición i + 1
    swap(A[i + 1], A[high]);
    return (i + 1);
}

void Ordenador::ordenamientoPorResiduos(uint32_t *A, uint32_t n) const {
    arrays.verificarOrden(A, n);
    auto inicio = high_resolution_clock::now();
    
    radixSort(A, n);

    auto fin = high_resolution_clock::now();
    arrays.verificarOrden(A, n);
    arrays.imprimirTiempo("radix sort", inicio, fin);
}

void Ordenador::radixSort(uint32_t *A, uint32_t n) const {
    // Determinar el número de bits por dígito (r = ⌊lg n⌋)
    uint32_t r = static_cast<uint32_t>(log2(n)); // Calcula r = ⌊lg n⌋
    uint32_t maxElem = A[0];

    // Encuentra el número máximo en A
    for (uint32_t i = 1; i < n; ++i) {
        if (A[i] > maxElem)
            maxElem = A[i];
    }

    // Para cada dígito (de menor a mayor), realizar el conteo de dígitos
    for (uint32_t exp = 1; maxElem / exp > 0; exp *= 2) {
        // Usar Counting Sort para el dígito correspondiente
        countingSort(A, n, exp, r);
    }
}

void Ordenador::countingSort(uint32_t *A, uint32_t n, uint32_t exp, uint32_t r) const {
    uint32_t *output = new uint32_t[n]; // Array de salida
    uint32_t *count = new uint32_t[1 << r](); // Array de conteo (con tamaño 2^r)

    // Contar las frecuencias de los dígitos
    for (uint32_t i = 0; i < n; ++i) {
        uint32_t digit = (A[i] >> exp) & ((1 << r) - 1); // Obtener el dígito correspondiente
        count[digit]++;
    }

    // Modificar el array de conteo para que contenga las posiciones acumuladas
    for (uint32_t i = 1; i < (1 << r); ++i) {
        count[i] += count[i - 1];
    }

    // Construir el array de salida utilizando los índices acumulados
    for (int32_t i = n - 1; i >= 0; --i) {
        uint32_t digit = (A[i] >> exp) & ((1 << r) - 1);
        output[count[digit] - 1] = A[i];
        count[digit]--;
    }

    // Copiar el array de salida a A
    for (uint32_t i = 0; i < n; ++i) {
        A[i] = output[i];
    }

    // Liberar memoria
    delete[] output;
    delete[] count;
}


constexpr const char* Ordenador::imprimirDatosDeTarea() const {
    return "Carné C36624, Nombre: Camila Rodríguez, Tarea 1";
}
