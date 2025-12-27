#pragma once
#include <iostream>
#include <stack>
#include <cstddef>   // para size_t
#include <vector>    // para std::vector

using namespace std;

template <typename DataType>
class BSTree;

template <typename DataType>
class BSTreeNode {
 public:
  friend class BSTree<DataType>;

  BSTreeNode() = default;

  // Constrcutor
  BSTreeNode(const DataType &value, BSTreeNode<DataType> *parent = nullptr,
             BSTreeNode<DataType> *left = nullptr,
             BSTreeNode<DataType> *right = nullptr)
      : key(value), parent(parent), left(left), right(right) {}

  // Destructor
  ~BSTreeNode() {}

  // Getters y Setters
  DataType getKey() const { return key; }

  BSTreeNode<DataType> *getParent() const { return parent; }

  BSTreeNode<DataType> *getLeft() const { return left; }

  BSTreeNode<DataType> *getRight() const { return right; }

  void setParent(BSTreeNode<DataType> *p) { parent = p; }

  void setLeft(BSTreeNode<DataType> *l) { left = l; }

  void setRight(BSTreeNode<DataType> *r) { right = r; }

 private:
  // Atributos
  DataType key;
  BSTreeNode<DataType> *parent = nullptr;
  BSTreeNode<DataType> *left = nullptr;
  BSTreeNode<DataType> *right = nullptr;
};

template <typename DataType>
class BSTree {
 public:

  // Constructor y Destructor
  BSTree() : root(nullptr) {}

  ~BSTree() {
    destroyTree(root);
    root = nullptr;
  }

  // Inserta un valor en el árbol
  void insert(const DataType &value) {

    // Si el árbol está vacío, creamos el nodo raíz
    BSTreeNode<DataType> *z = new BSTreeNode<DataType>(value);
    BSTreeNode<DataType> *y = nullptr;
    BSTreeNode<DataType> *x = root;

    // Buscamos la posición correcta para insertar el nuevo nodo
    while (x != nullptr) {
      y = x;
      if (z->key < x->key)
        x = x->left;
      else
        x = x->right;
    }

    z->parent = y;

    if (y == nullptr)
      root = z;
    else if (z->key < y->key)
      y->left = z;
    else
      y->right = z;
  }

  // Borrar un valor en el árbol
  void remove(const DataType &value) {
    BSTreeNode<DataType> *z = search(root, value);
    if (z == nullptr)
      return;

    if (z->left == nullptr)
      swap(z, z->right);
    else if (z->right == nullptr)
      swap(z, z->left);
    else {
      BSTreeNode<DataType> *y = getMinimum(z->right);
      if (y->parent != z) {
        swap(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      swap(z, y);
      y->left = z->left;
      y->left->parent = y;
    }

    delete z;
  }

  // Imprime el árbol en orden
  void inorderWalk(BSTreeNode<DataType> *rootOfSubtree) const {
    std::stack<BSTreeNode<DataType> *> pila;
    BSTreeNode<DataType> *actual = rootOfSubtree;

    while (!pila.empty() || actual != nullptr) {
      if (actual != nullptr) {
        pila.push(actual);
        actual = actual->left;
      } else {
        actual = pila.top();
        pila.pop();
        std::cout << actual->key << " ";
        actual = actual->right;
      }
    }
  }

  // Búsqueda de un valor en el árbol	
  BSTreeNode<DataType> *search(const BSTreeNode<DataType> *rootOfSubtree,
                               const DataType &value) const {
    BSTreeNode<DataType> *actual = const_cast<BSTreeNode<DataType> *>(rootOfSubtree);
    while (actual != nullptr && value != actual->key) {
      if (value < actual->key)
        actual = actual->left;
      else
        actual = actual->right;
    }
    return actual;
  }

  // Obtener el mínimo
  BSTreeNode<DataType> *getMinimum(
      const BSTreeNode<DataType> *rootOfSubtree) const {
    BSTreeNode<DataType> *actual = const_cast<BSTreeNode<DataType> *>(rootOfSubtree);
    while (actual && actual->left != nullptr)
      actual = actual->left;
    return actual;
  }

  // Obtener el máximo
  BSTreeNode<DataType> *getMaximum(
      const BSTreeNode<DataType> *rootOfSubtree) const {
    BSTreeNode<DataType> *actual = const_cast<BSTreeNode<DataType> *>(rootOfSubtree);
    while (actual && actual->right != nullptr)
      actual = actual->right;
    return actual;
  }

  // Obtener el sucesor
  BSTreeNode<DataType> *getSuccessor(const BSTreeNode<DataType> *node) const {
    if (node->right != nullptr)
      return getMinimum(node->right);

    BSTreeNode<DataType> *y = node->parent;
    BSTreeNode<DataType> *x = const_cast<BSTreeNode<DataType> *>(node);
    while (y != nullptr && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  // Obtener el raíz
  BSTreeNode<DataType> *getRoot() const {
    return root;
  }

  bool fastInsert(const DataType &value) {
    BSTreeNode<DataType> *y = nullptr;
    BSTreeNode<DataType> *x = root;

    // Buscamos la posición correcta para insertar el nuevo nodo
    // mientras verificamos duplicados
    while (x != nullptr) {
      y = x;
      if (value < x->key) {
        x = x->left;
      } else if (value > x->key) {
        x = x->right;
      } else {
        // El valor ya existe, no insertar
        return false;
      }
    }

    // Crear el nuevo nodo solo si no existe
    BSTreeNode<DataType> *z = new BSTreeNode<DataType>(value);
    z->parent = y;

    if (y == nullptr) {
      root = z;  // Árbol vacío
    } else if (value < y->key) {
      y->left = z;
    } else {
      y->right = z;
    }

    return true;  // Inserción exitosa
  }
  
 private:
  BSTreeNode<DataType> *root = nullptr;

  // Funciones auxiliares
  void destroyTree(BSTreeNode<DataType>* node) {
    if (node == nullptr) return;
    
    stack<BSTreeNode<DataType>*> stack1;
    stack<BSTreeNode<DataType>*> stack2;
    stack1.push(node);
    
    while (!stack1.empty()) {
        auto current = stack1.top();
        stack1.pop();
        stack2.push(current);
        
        if (current->left) stack1.push(current->left);
        if (current->right) stack1.push(current->right);
    }
    
    while (!stack2.empty()) {
        auto current = stack2.top();
        stack2.pop();
        delete current;
    }
}

  void swap(BSTreeNode<DataType> *u, BSTreeNode<DataType> *v) {
    if (u->parent == nullptr)
      root = v;
    else if (u == u->parent->left)
      u->parent->left = v;
    else
      u->parent->right = v;
    if (v != nullptr)
      v->parent = u->parent;
  }
};
