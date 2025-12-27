#include "Controlador.hpp"
#include "GenerarArray.hpp"
#include "SinglyLinkedList.hpp"

#include <iostream>
#include <vector>
#include <chrono>
#include <cstddef>   // para size_t
#include <random>

using namespace std;
using namespace std::chrono; // Para medir el tiempo

Controlador::Controlador() = default;

// ==== Lista Enlazada Simple ===

void Controlador::insercionAleatoria() {
    cout << "\n[SLL] Inserción Aleatoria" << endl;

    vector<int> datos = generador.generarRandom(n);

    // Insertar los datos generados en la lista enlazada
    for (int valor : datos) {
        lista.insert(valor);
    }
}

void Controlador::busquedaAleatoria() {
    cout << "\n[SLL] Búsqueda Aleatoria" << endl;

    vector<int> elementos; // Vector para almacenar los elementos a buscar
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, rango - 1); // Distribución uniforme entre 0 y rango-1

    for (size_t i = 0; i < e; ++i) {
        elementos.push_back(dist(gen));
    }

    medirTiempoBusqueda(elementos);
}

void Controlador::eliminacionAleatoria() {
    cout << "\n[SLL] Eliminación Aleatoria" << endl;

    // Generar e elementos aleatorios para eliminar
    vector<int> elementos;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, rango - 1);

    for (size_t i = 0; i < e; ++i) {
        elementos.push_back(dist(gen));
    }

    medirTiempoEliminacion(elementos);
}


void Controlador::insercionOrdenada() {
    lista.clear(); // Limpiar la lista antes de la inserción ordenada
    cout << "\n[SLL] Inserción Ordenada" << endl;

    // Llenar la lista enlazada con valores ordenados del 0 al n-1
    for (size_t i = 0; i < n; ++i) {
        lista.insert(static_cast<int>(i));
    }
}

void Controlador::busquedaOrdenada() {
    cout << "\n[SLL] Búsqueda Ordenada" << endl;

    // Generar e elementos aleatorios para buscar en la lista ordenada
    vector<int> elementos;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, rango - 1);

    // Buscar e elementos aleatorios en el rango especificado
    for (size_t i = 0; i < e; ++i) {
        elementos.push_back(dist(gen));
    }

    medirTiempoBusqueda(elementos);
}

void Controlador::eliminacionOrdenada() {
    cout << "\n[SLL] Eliminación Ordenada" << endl;

    // Generar e elementos aleatorios para eliminar de la lista ordenada
    vector<int> elementos;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, rango - 1);

 
    for (size_t i = 0; i < e; ++i) {
        elementos.push_back(dist(gen));
    }

    medirTiempoEliminacion(elementos);
}

// Métodos para medir el tiempo de búsqueda y eliminación
void Controlador::medirTiempoBusqueda(const vector<int>& elementos) {

    // Inicializar el temporizador
    auto inicio = high_resolution_clock::now();

    // Buscar cada elemento en la lista enlazada
    for (int valor : elementos) {
        lista.search(valor);
    }

    // Finalizar el temporizador
    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;

    // Mostrar el Tiempo de búsqueda
    cout << "Tiempo de búsqueda: " << duracion.count() << " secs." << endl;
}

void Controlador::medirTiempoEliminacion(const vector<int>& elementos) {

    // Inicializar el temporizador
    auto inicio = high_resolution_clock::now();

    // Eliminar cada elemento de la lista enlazada
    for (int valor : elementos) {
        lista.remove(valor);
    }

    // Finalizar el temporizador
    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;

    // Mostrar el Tiempo de eliminación
    cout << "Tiempo de eliminación: " << duracion.count() << " secs." << endl;
}
// ==== Árbol Binario de Búsqueda ===

void Controlador::insercionAleatoriaABB() {
    cout << "\n[ABB] Inserción Aleatoria" << endl;
    vector<int> datos = generador.generarRandom(n);

    for (int valor : datos) {
        abb.fastInsert(valor);
    }
}

void Controlador::busquedaAleatoriaABB() {
    cout << "\n[ABB] Búsqueda Aleatoria" << endl;

    vector<int> elementos;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, rango - 1);

    for (size_t i = 0; i < e; ++i) {
        elementos.push_back(dist(gen));
    }

    medirTiempoBusquedaABB(elementos,abb);
}

void Controlador::eliminacionAleatoriaABB() {
    cout << "\n[ABB] Eliminación Aleatoria" << endl;

    vector<int> elementos;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, rango - 1);

    for (size_t i = 0; i < e; ++i) {
        elementos.push_back(dist(gen));
    }

    medirTiempoEliminacionABB(elementos,abb);
}

// Inserción ordenada  
void Controlador::insercionOrdenadaABB() {
     // Limpiar el árbol antes de la inserción ordenada
    cout << "\n[ABB] Inserción Ordenada" << endl;
    abbO = BSTree<int>();  // hacer otro árbol
    abbO.insert(n);    // método que debes definir
}

void Controlador::busquedaOrdenadaABB() {
    cout << "\n[ABB] Búsqueda Ordenada" << endl;

    vector<int> elementos;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, rango - 1);

    for (size_t i = 0; i < e; ++i) {
        elementos.push_back(dist(gen));
    }

    medirTiempoBusquedaABB(elementos,abbO);
}

void Controlador::eliminacionOrdenadaABB() {
    cout << "\n[ABB] Eliminación Ordenada" << endl;

    vector<int> elementos;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, rango - 1);

    for (size_t i = 0; i < e; ++i) {
        elementos.push_back(dist(gen));
    }

    medirTiempoEliminacionABB(elementos,abbO);
}

// Medición de tiempo

void Controlador::medirTiempoBusquedaABB(const vector<int>& elementos, 
                                         BSTree<int>& abb) {
    auto inicio = high_resolution_clock::now();

    for (int valor : elementos) {
        abb.search(abb.getRoot(), valor);
    }

    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;

    cout << "Tiempo de búsqueda: " << duracion.count() << " secs." << endl;
}

void Controlador::medirTiempoEliminacionABB(const vector<int>& elementos, 
                                            BSTree<int>& abb) {
    auto inicio = high_resolution_clock::now();

    for (int valor : elementos) {
        abb.remove(valor);
    }

    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;

    cout << "Tiempo de eliminación: " << duracion.count() << " secs." << endl;
}

// ==== Tabla Hash Encadenada ===

// Inserción Aleatoria
void Controlador::insercionAleatoriaCHT() {
    cout << "\n[CHT] Inserción Aleatoria" << endl;
    vector<int> datos = generador.generarRandom(n);
    
    for (int valor : datos) {
        cht_aleatoria.insert(valor);
    }
}

// Búsqueda Aleatoria
void Controlador::busquedaAleatoriaCHT() {
    cout << "\n[CHT] Búsqueda Aleatoria" << endl;
    
    vector<int> elementos;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, rango - 1);
    
    for (size_t i = 0; i < e; ++i) {
        elementos.push_back(dist(gen));
    }
    
    medirTiempoBusquedaCHT(elementos, cht_aleatoria);
}

// Eliminación Aleatoria
void Controlador::eliminacionAleatoriaCHT() {
    cout << "\n[CHT] Eliminación Aleatoria" << endl;
    
    vector<int> elementos;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, rango - 1);
    
    for (size_t i = 0; i < e; ++i) {
        elementos.push_back(dist(gen));
    }
    
    medirTiempoEliminacionCHT(elementos, cht_aleatoria);
}

// Inserción Ordenada
void Controlador::insercionOrdenadaCHT() {
    cout << "\n[CHT] Inserción Ordenada" << endl;
    
    // Insertar claves ordenadas 0, 1, ..., n-1
    for (size_t i = 0; i < n; ++i) {
        cht_ordenada.insert(static_cast<int>(i));
    }
}

// Búsqueda Ordenada
void Controlador::busquedaOrdenadaCHT() {
    cout << "\n[CHT] Búsqueda Ordenada" << endl;
    
    vector<int> elementos;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, rango - 1);
    
    for (size_t i = 0; i < e; ++i) {
        elementos.push_back(dist(gen));
    }
    
    medirTiempoBusquedaCHT(elementos, cht_ordenada);
}

// Eliminación Ordenada
void Controlador::eliminacionOrdenadaCHT() {
    cout << "\n[CHT] Eliminación Ordenada" << endl;
    
    vector<int> elementos;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, rango - 1);
    
    for (size_t i = 0; i < e; ++i) {
        elementos.push_back(dist(gen));
    }
    
    medirTiempoEliminacionCHT(elementos, cht_ordenada);
}

// Métodos de medición para CHT
void Controlador::medirTiempoBusquedaCHT(const vector<int>& elementos, ChainedHashTable<int>& tabla) {
    auto inicio = high_resolution_clock::now();
    
    for (int valor : elementos) {
        tabla.search(valor);  // Buscar sin usar el resultado
    }
    
    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    
    cout << "Tiempo de búsqueda: " << duracion.count() << " secs." << endl;
}

void Controlador::medirTiempoEliminacionCHT(const vector<int>& elementos, ChainedHashTable<int>& tabla) {
    auto inicio = high_resolution_clock::now();
    
    for (int valor : elementos) {
        tabla.remove(valor);  // Eliminar el elemento
    }
    
    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    
    cout << "Tiempo de eliminación: " << duracion.count() << " secs." << endl;
}

// ==== Árbol Rojo-Negro ====

void Controlador::insercionAleatoriaRBT() {
    cout << "\n[RBTree] Inserción Aleatoria" << endl;
    vector<int> datos = generador.generarRandom(n);
    for (int valor : datos) {
        rbtree.insert(valor);
    }
}

void Controlador::busquedaAleatoriaRBT() {
    cout << "\n[RBTree] Búsqueda Aleatoria" << endl;
    vector<int> elementos;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, rango - 1);
    for (size_t i = 0; i < e; ++i) {
        elementos.push_back(dist(gen));
    }
    medirTiempoBusquedaRBT(elementos, rbtree);
}

void Controlador::eliminacionAleatoriaRBT() {
    cout << "\n[RBTree] Eliminación Aleatoria" << endl;
    vector<int> elementos;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, rango - 1);
    for (size_t i = 0; i < e; ++i) {
        elementos.push_back(dist(gen));
    }
    medirTiempoEliminacionRBT(elementos, rbtree);
}

void Controlador::insercionOrdenadaRBT() {
    cout << "\n[RBTree] Inserción Ordenada" << endl;
    rbtreeO = RBTree<int>();
    for (int i = 0; i < static_cast<int>(n); ++i) {
        rbtreeO.insert(i);
    }
}

void Controlador::busquedaOrdenadaRBT() {
    cout << "\n[RBTree] Búsqueda Ordenada" << endl;
    vector<int> elementos;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, rango - 1);
    for (size_t i = 0; i < e; ++i) {
        elementos.push_back(dist(gen));
    }
    medirTiempoBusquedaRBT(elementos, rbtreeO);
}

void Controlador::eliminacionOrdenadaRBT() {
    cout << "\n[RBTree] Eliminación Ordenada" << endl;
    vector<int> elementos;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, rango - 1);
    for (size_t i = 0; i < e; ++i) {
        elementos.push_back(dist(gen));
    }
    medirTiempoEliminacionRBT(elementos, rbtreeO);
}

void Controlador::medirTiempoBusquedaRBT(const vector<int>& elementos, RBTree<int>& tree) {
    auto inicio = high_resolution_clock::now();
    for (int valor : elementos) {
        tree.search(tree.getRoot(), valor);
    }
    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    cout << "Tiempo de búsqueda:" << duracion.count() << " secs." << endl;
}

void Controlador::medirTiempoEliminacionRBT(const vector<int>& elementos, RBTree<int>& tree) {
    auto inicio = high_resolution_clock::now();
    for (int valor : elementos) {
        tree.remove(valor);
    }
    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    cout << "Tiempo de eliminación:" << duracion.count() << " secs." << endl;
}
