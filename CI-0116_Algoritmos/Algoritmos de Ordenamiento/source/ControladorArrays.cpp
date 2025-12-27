#include "ControladorArrays.hpp"
#include "Ordenador.hpp"

using namespace std;
using namespace std::chrono;

Ordenador ordenador;

// Método para crear arrays de tamaño n con números aleatorios
uint32_t* ControladorArrays::crearArray(uint32_t n) {
    uint32_t* array = new uint32_t[n];
    cout << "Creando array de " << n << " elementos." << endl;
    for (uint32_t i = 0; i < n; ++i) {
        array[i] = rand() % 100;
    }
    return array;
}

void ControladorArrays::destruirArray(uint32_t* A) {
    delete[] A;
}

void ControladorArrays::imprimirArray(uint32_t* A, uint32_t n) {
    for (uint32_t i = 0; i < n; ++i)
        cout << A[i] << " ";
    cout << endl;
}

bool ControladorArrays::verificarOrden(uint32_t* A, uint32_t n) {
    for (uint32_t i = 1; i < n; ++i) {
        if (A[i - 1] > A[i]) {
            cout << "El array no está ordenado." << endl;
            return false;
        }
    }
    cout << "El array está ordenado." << endl;
    return true;
}

// Método para copiar un array
uint32_t* ControladorArrays::copiarArray(uint32_t* original, uint32_t n) {
    uint32_t* copia = new uint32_t[n];
    for (uint32_t i = 0; i < n; ++i) {
        copia[i] = original[i];
    }
    return copia;
}

void ControladorArrays::GenerarPruebasAlgoritmo(uint32_t* mil,
    uint32_t* diezMil, uint32_t* cienMil, uint32_t* unMillon, string Algoritmo) {

    cout << "\n ===== Ejecutando algoritmo: " << Algoritmo << " =====" << endl;

    uint32_t* copiaMil = copiarArray(mil, 1000);
    uint32_t* copiaDiezMil = copiarArray(diezMil, 10000);
    uint32_t* copiaCienMil = copiarArray(cienMil, 100000);
    uint32_t* copiaUnMillon = copiarArray(unMillon, 1000000);

    if (Algoritmo == "Seleccion") {
        cout << "--- Mil Elementos ---" << endl;
        ordenador.ordenamientoPorSeleccion(copiaMil, 1000);
        cout << "--- Diez Mil Elementos ---" << endl;
        ordenador.ordenamientoPorSeleccion(copiaDiezMil, 10000);
        cout << "--- Cien Mil Elementos ---" << endl;
        ordenador.ordenamientoPorSeleccion(copiaCienMil, 100000);
        cout << "--- Un Millón de Elementos ---" << endl;
        ordenador.ordenamientoPorSeleccion(copiaUnMillon, 1000000);
    }
    else if (Algoritmo == "Inserccion") {
        cout << "--- Mil Elementos ---" << endl;
        ordenador.ordenamientoPorInserccion(copiaMil, 1000);
        cout << "--- Diez Mil Elementos ---" << endl;
        ordenador.ordenamientoPorInserccion(copiaDiezMil, 10000);
        cout << "--- Cien Mil Elementos ---" << endl;
        ordenador.ordenamientoPorInserccion(copiaCienMil, 100000);
        cout << "--- Un Millón de Elementos ---" << endl;
        ordenador.ordenamientoPorInserccion(copiaUnMillon, 1000000);
    }
    else if (Algoritmo == "Mezcla") {
        cout << "--- Mil Elementos ---" << endl;
        ordenador.ordenamientoPorMezcla(copiaMil, 1000);
        cout << "--- Diez Mil Elementos ---" << endl;
        ordenador.ordenamientoPorMezcla(copiaDiezMil, 10000);
        cout << "--- Cien Mil Elementos ---" << endl;
        ordenador.ordenamientoPorMezcla(copiaCienMil, 100000);
        cout << "--- Un Millón de Elementos ---" << endl;
        ordenador.ordenamientoPorMezcla(copiaUnMillon, 1000000);
    }
    else if (Algoritmo == "Monticulos") {
        cout << "--- Mil Elementos ---" << endl;
        ordenador.ordenamientoPorMonticulos(copiaMil, 1000);
        cout << "--- Diez Mil Elementos ---" << endl;
        ordenador.ordenamientoPorMonticulos(copiaDiezMil, 10000);
        cout << "--- Cien Mil Elementos ---" << endl;
        ordenador.ordenamientoPorMonticulos(copiaCienMil, 100000);
        cout << "--- Un Millón de Elementos ---" << endl;
        ordenador.ordenamientoPorMonticulos(copiaUnMillon, 1000000);
    }
    else if (Algoritmo == "Rapido") {
        cout << "--- Mil Elementos ---" << endl;
        ordenador.ordenamientoRapido(copiaMil, 1000);
        cout << "--- Diez Mil Elementos ---" << endl;
        ordenador.ordenamientoRapido(copiaDiezMil, 10000);
        cout << "--- Cien Mil Elementos ---" << endl;
        ordenador.ordenamientoRapido(copiaCienMil, 100000);
        cout << "--- Un Millón de Elementos ---" << endl;
        ordenador.ordenamientoRapido(copiaUnMillon, 1000000);
    }
    else if (Algoritmo == "Residuos") {
        cout << "--- Mil Elementos ---" << endl;
        ordenador.ordenamientoPorResiduos(copiaMil, 1000);
        cout << "--- Diez Mil Elementos ---" << endl;
        ordenador.ordenamientoPorResiduos(copiaDiezMil, 10000);
        cout << "--- Cien Mil Elementos ---" << endl;
        ordenador.ordenamientoPorResiduos(copiaCienMil, 100000);
        cout << "--- Un Millón de Elementos ---" << endl;
        ordenador.ordenamientoPorResiduos(copiaUnMillon, 1000000);
    }
    else {
        cout << "Algoritmo no reconocido." << endl;
    }

    // Liberar memoria de las copias
    destruirArray(copiaMil);
    destruirArray(copiaDiezMil);
    destruirArray(copiaCienMil);
    destruirArray(copiaUnMillon);
}

// Método principal de ejecución
void ControladorArrays::Ejecutar() {
    srand(static_cast<unsigned>(time(0))); // Inicializar la semilla para números aleatorios
    // Tamaños
    uint32_t mil = 1000;
    uint32_t diezMil = 10000;
    uint32_t cienMil = 100000;
    uint32_t unMillon = 1000000;

    // Crear arrays
    cout << "Creando arrays ..." << endl;
    uint32_t* arrayMil = crearArray(mil);
    uint32_t* arrayDiezMil = crearArray(diezMil);
    uint32_t* arrayCienMil = crearArray(cienMil);
    uint32_t* arrayUnMillon = crearArray(unMillon);

    // Ejecutar algoritmos
    cout << "Ejecutando algoritmos... \n" << endl;
    GenerarPruebasAlgoritmo(arrayMil, arrayDiezMil, arrayCienMil, arrayUnMillon, "Seleccion");
    GenerarPruebasAlgoritmo(arrayMil, arrayDiezMil, arrayCienMil, arrayUnMillon, "Inserccion");
    GenerarPruebasAlgoritmo(arrayMil, arrayDiezMil, arrayCienMil, arrayUnMillon, "Mezcla");
    GenerarPruebasAlgoritmo(arrayMil, arrayDiezMil, arrayCienMil, arrayUnMillon, "Monticulos");
    GenerarPruebasAlgoritmo(arrayMil, arrayDiezMil, arrayCienMil, arrayUnMillon, "Rapido");
    GenerarPruebasAlgoritmo(arrayMil, arrayDiezMil, arrayCienMil, arrayUnMillon, "Residuos");

    // Liberar memoria
    cout << "Liberando memoria..." << endl;
    destruirArray(arrayMil);
    destruirArray(arrayDiezMil);
    destruirArray(arrayCienMil);
    destruirArray(arrayUnMillon);
    cout << "Memoria liberada." << endl;
}

// Imprimir duración de ejecución
void ControladorArrays::imprimirTiempo(const string& nombre, high_resolution_clock::time_point inicio, high_resolution_clock::time_point fin) {
    auto duracion_us = duration_cast<microseconds>(fin - inicio).count();
    auto duracion_s = duracion_us / 1'000'000;
    int minutos = duracion_s / 60;
    int segundos = duracion_s % 60;

    cout << "Tiempo de " << nombre << ": "
         << minutos << " min " << segundos << " s, "
         << duracion_us << " microsegundos \n " << endl;
}
