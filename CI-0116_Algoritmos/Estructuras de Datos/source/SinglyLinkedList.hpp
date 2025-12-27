/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
*/
#include <cstddef>   // para size_t
#include <vector>    // para std::vector
#pragma once

template <typename DataType>
class SLList;

template <typename DataType>
class SLListNode {
public:
    friend class SLList<DataType>;

    SLListNode() : next(nullptr) {}

    // Constructor y Destructor
    SLListNode(const DataType& value, SLListNode<DataType>* next = nullptr) 
        : key(value), next(next) {}
    
    ~SLListNode() = default;

    // Getters y Setters
    DataType getKey() const {
        return key;
    }

    SLListNode<DataType>* getNext() const {
        return next;
    }

    void setKey(DataType key) {
        this->key = key;
    }

    void setNext(SLListNode<DataType>* newNode) {
        next = newNode;
    }

private:
    // Atributos
    DataType key;
    SLListNode<DataType>* next;
};

template <typename DataType>
class SLList {
public:
    // Constructor 
    SLList() {
        nil = new SLListNode<DataType>();  // Nodo centinela
        nil->setNext(nullptr);              // Lista vacía
    }

    // Destructor
    ~SLList() {
        SLListNode<DataType>* current = nil->getNext();
        while (current != nullptr) {
            SLListNode<DataType>* temp = current;
            current = current->getNext();
            delete temp;
        }
        delete nil;  // Liberar nodo centinela
    }

    // Insertar valor 
    void insert(const DataType& value) {
        SLListNode<DataType>* newNode = new SLListNode<DataType>(value);
        newNode->setNext(nil->getNext());
        nil->setNext(newNode);
    }

    // Buscar valor 
    SLListNode<DataType>* search(const DataType& value) const {
        SLListNode<DataType>* current = nil->getNext();
        while (current != nullptr) {
            if (current->getKey() == value) {
                return current;
            }
            current = current->getNext();
        }
        return nullptr;
    }

    // Eliminar valor 
    void remove(const DataType& value) {
        SLListNode<DataType>* prev = nil;
        SLListNode<DataType>* current = nil->getNext();
        
        while (current != nullptr) {
            if (current->getKey() == value) {
                prev->setNext(current->getNext());
                delete current;
                return;
            }
            prev = current;
            current = current->getNext();
        }
    }

    // Obtener nodo centinela
    SLListNode<DataType>* getNil() const {
        return nil;
    }

// Vaciar la lista completamente
void clear() {
    SLListNode<DataType>* current = nil->getNext();
    while (current != nullptr) {
        SLListNode<DataType>* temp = current;
        current = current->getNext();
        delete temp;
    }
    nil->setNext(nullptr);  // La lista ahora está vacía
}


private:
    SLListNode<DataType>* nil;  // Nodo centinela
};