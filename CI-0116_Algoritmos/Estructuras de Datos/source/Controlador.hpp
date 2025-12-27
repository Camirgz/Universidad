#include <vector>
#include <cstddef>
#include "SinglyLinkedList.hpp"
#include "GenerarArray.hpp"
#include "BinarySearchTree.hpp"
#include "ChainedHashTable.hpp"
#include "RedBlackTree.hpp"

#ifndef CONTROLADOR_HPP
#define CONTROLADOR_HPP

class Controlador {
public:
    Controlador();
    
    void insercionAleatoria();
    void busquedaAleatoria();
    void eliminacionAleatoria();

    void insercionOrdenada();
    void busquedaOrdenada();
    void eliminacionOrdenada();

    // ABB
    void insercionAleatoriaABB();
    void busquedaAleatoriaABB();
    void eliminacionAleatoriaABB();

    void insercionOrdenadaABB();  // con fastInsert
    void busquedaOrdenadaABB();
    void eliminacionOrdenadaABB();

    // Tabla Hash Encadenada
    void insercionAleatoriaCHT();
    void busquedaAleatoriaCHT();
    void eliminacionAleatoriaCHT();
    
    void insercionOrdenadaCHT();
    void busquedaOrdenadaCHT();
    void eliminacionOrdenadaCHT();

    // Árbol rojo y negro
    void insercionAleatoriaRBT();
    void busquedaAleatoriaRBT();
    void eliminacionAleatoriaRBT();
    void insercionOrdenadaRBT();
    void busquedaOrdenadaRBT();
    void eliminacionOrdenadaRBT();



private:

    static const size_t n = 1000000;
    static const size_t e = 10000;
    static const int rango = 3 * static_cast<int>(n);

    // Instancias de las estructuras de datos
    BSTree<int> abb; 
    BSTree<int> abbO; 
    SLList<int> lista;
    ChainedHashTable<int> cht_aleatoria{n};  // Para inserción aleatoria
    ChainedHashTable<int> cht_ordenada{n};                 // Lista enlazada
    RBTree<int> rbtree;
    RBTree<int> rbtreeO; // para inserciones ordenadas
    GenerarArray generador;       // Generador de arreglos

    // Métodos para medir tiempos
    void medirTiempoBusqueda(const std::vector<int>& elementos);
    void medirTiempoEliminacion(const std::vector<int>& elementos);
    void medirTiempoBusquedaABB(const vector<int>& elementos, BSTree<int>& abb);
    void medirTiempoEliminacionABB(const vector<int>& elementos, BSTree<int>& abb);
    void medirTiempoBusquedaCHT(const std::vector<int>& elementos, ChainedHashTable<int>& tabla);
    void medirTiempoEliminacionCHT(const std::vector<int>& elementos, ChainedHashTable<int>& tabla);
    void medirTiempoBusquedaRBT(const std::vector<int>& elementos, RBTree<int>& arbol);
void medirTiempoEliminacionRBT(const std::vector<int>& elementos, RBTree<int>& arbol);
};

#endif // CONTROLADOR_HPP
