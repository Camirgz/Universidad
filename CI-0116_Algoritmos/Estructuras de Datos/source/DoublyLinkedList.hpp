#pragma once

#include <cstddef>   // para size_t
#include <vector>    // para std::vector

// Forward declaration
template <typename DataType>
class DLList;

template <typename DataType>
class DLListNode {
 public:
  friend class DLList<DataType>;

  // Constructor y Destructor
  DLListNode() = default;

  DLListNode(const DataType& value, DLListNode<DataType>* next = nullptr,
             DLListNode<DataType>* prev = nullptr)
      : key(value), next(next), prev(prev) {}

  ~DLListNode() {}

  // Getters y Setters
  DataType getKey() const {
    return key;
  }

  DLListNode<DataType>* getPrev() const {
    return prev;
  }

  DLListNode<DataType>* getNext() const {
    return next;
  }

  void setKey(DataType key) {
    this->key = key;
  }

  void setPrev(DLListNode<DataType>* prev) {
    this->prev = prev;
  }

  void setNext(DLListNode<DataType>* next) {
    this->next = next;
  }

 private:
  // Atributos
  DataType key;
  DLListNode<DataType>* next = nullptr;
  DLListNode<DataType>* prev = nullptr;
};

template <typename DataType>
class DLList {
 public:

  // Constructor y Destructor
  DLList() {
    nil = nullptr;
  }

  ~DLList() {
    DLListNode<DataType>* current = nil;
    while (current != nullptr) {
      DLListNode<DataType>* temp = current;
      current = current->next;
      delete temp;
    }
  }

  // Inserta al inicio 
  void insert(const DataType& value) {
    DLListNode<DataType>* newNode = new DLListNode<DataType>(value);
    newNode->next = nil;
    newNode->prev = nullptr;
    if (nil != nullptr) {
      nil->prev = newNode;
    }
    nil = newNode;
  }

  void insertFront(const DataType& value) {
  DLListNode<DataType>* newNode = new DLListNode<DataType>(value);
  newNode->next = nil;
  newNode->prev = nullptr;
  if (nil != nullptr) {
    nil->prev = newNode;
  }
  nil = newNode;
}

  // Busca un valor
  DLListNode<DataType>* search(const DataType& value) const {
    DLListNode<DataType>* current = nil;
    while (current != nullptr) {
      if (current->key == value) {
        return current;
      }
      current = current->next;
    }
    return nullptr;
  }

  // Borrar el primer nodo que contenga el valor
  void remove(const DataType& value) {
    DLListNode<DataType>* node = search(value);
    if (node != nullptr) {
      remove(node);
    }
  }

  // Borrar un nodo específico
  void remove(DLListNode<DataType>* node) {
    if (node == nullptr) return;

    if (node->prev != nullptr) {
      node->prev->next = node->next;
    } else {
      nil = node->next; // si eliminamos el primero
    }

    if (node->next != nullptr) {
      node->next->prev = node->prev;
    }

    delete node;
  }

  // Obtener el nodo centinela
  DLListNode<DataType>* getNil() const {
    return nil;
  }

  // Obtener la cabeza de la lista
  DLListNode<DataType>* getHead() const {
    return nil;
  }


 private:
  DLListNode<DataType>* nil;  // Apunta al primer nodo inicialmente, es el nodo centinela
};
