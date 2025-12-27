#include <iostream>
#include <sstream>
#include "../include/nodo.h"

template <typename T>
class ArbolB {
public:
    Nodo<T>* root;
    
    ArbolB() {
        root = nullptr;
    }
    
    Nodo<T>* insertar(T dato) {
        if (root == nullptr) {
            root = new Nodo<T>(dato);
            return root;
        } else {
            Nodo<T>* padre = nullptr;
            Nodo<T>* actual = root;
            char cual = 'R';
            while (actual != nullptr) {
                padre = actual;
                if (dato < actual->dato) {
                    actual = actual->left;
                    cual = 'L';
                } else {
                    actual = actual->right;
                    cual = 'R';
                }
            }
            
            if (cual == 'L') {
                padre->left = new Nodo<T>(dato);
                actual = padre->left;
            } else {
                padre->right = new Nodo<T>(dato);
                actual = padre->right;
            }
            
            return actual;
        }
    }
    
    void imprimir(Nodo<T>* nodo, std::stringstream& ss) { // recorrido profundidad in-order
        if (nodo != nullptr) {
            imprimir(nodo->left, ss);
            std::string espacio = (ss.str().empty()) ? "" : " ";
            ss << espacio << nodo->dato;
            imprimir(nodo->right, ss);
        }
    }

    Nodo<T>* eliminar(Nodo<T>* nodo, T dato) {
        if (nodo == nullptr) {
            return nodo; 
        }

        if (dato < nodo->dato) { 
            nodo->left = eliminar(nodo->left, dato);
        } else if (dato > nodo->dato) { 
            nodo->right = eliminar(nodo->right, dato);
        } else {
            
            if (nodo->left == nullptr) {
                Nodo<T>* temp = nodo->right;
                delete nodo;
                return temp;
            } else if (nodo->right == nullptr) {
                Nodo<T>* temp = nodo->left;
                delete nodo;
                return temp;
            }

            
            Nodo<T>* temp = minimoNodo(nodo->right);
            nodo->dato = temp->dato;
            nodo->right = eliminar(nodo->right, temp->dato);
        }

        return nodo;
    }
    
    Nodo<T>* minimoNodo(Nodo<T>* nodo) {
        Nodo<T>* actual = nodo;
        while (actual && actual->left != nullptr) {
            actual = actual->left;
        }
        return actual;
    }
};
