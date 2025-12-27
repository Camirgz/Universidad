#ifndef NODO_H
#define NODO_H
#include <cstddef>

template <typename T>
class Nodo{
 public:
    T dato;
    Nodo* left;
    Nodo* right;
    Nodo(T dato){
        this->dato = dato;
        this->left = NULL;
        this->right = NULL;
    }
};

#endif