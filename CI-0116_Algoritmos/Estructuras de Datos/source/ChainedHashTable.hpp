/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
 */

#pragma once
#include <cstdint>
#include <vector>
#include <cstddef>   // para size_t
#include <vector>    // para std::vector


#include "DoublyLinkedList.hpp"

template <typename DataType>
class ChainedHashTable {
 public:
  // Constructor
  ChainedHashTable(size_t size) : size(size), table(size) {}

  //  Destructor
  ~ChainedHashTable() {}

  //  Insertar un valor
  void insert(const DataType& value) {
        size_t index = hashFunction(value);
        
        // Verificar si el valor ya existe
        if (search(value) == nullptr) {
            table[index].insertFront(value);
        }
        // Si ya existe, no hacer nada (evita duplicados)
  }

  //  Búsqueda
  DLListNode<DataType>* search(const DataType& value) const {
    size_t index = hashFunction(value);
    DLListNode<DataType>* current = table[index].getHead();

    while (current != nullptr) {
      if (current->getKey() == value) {
        return current;
      }
      current = current->getNext();
    }
    return nullptr;
  }

  //  Eliminar un valor
  void remove(const DataType& value) {
    size_t index = hashFunction(value);
    table[index].remove(value);
  }

  // Obtener el tamaño de la tabla
  size_t getSize() const {
    return size;
  }

  // Obtener la tabla entera
  std::vector<DLList<DataType>> getTable() const {
    return table;
  }

  // Establecer una nueva tabla
  void setTable(std::vector<DLList<DataType>> newTable) {
    table = newTable;
    size = newTable.size();
  }

 private:
  size_t size;
  std::vector<DLList<DataType>> table;

  // Función hash simple (usando std::hash)
  size_t hashFunction(const DataType& value) const {
    return std::hash<DataType>{}(value) % size;
  }
};
