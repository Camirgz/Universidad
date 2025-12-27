#pragma once
#include <iostream>
#include <stack>
#include <cstddef>   // para size_t
#include <vector>    // para std::vector

enum colors { RED, BLACK };

template <typename DataType>
class RBTree;

template <typename DataType>
class RBTreeNode {
 public:
  friend class RBTree<DataType>;

  RBTreeNode() = default;

  // Constructor
  RBTreeNode(const DataType &value, RBTreeNode<DataType> *parent = nullptr,
             RBTreeNode<DataType> *left = nullptr,
             RBTreeNode<DataType> *right = nullptr, enum colors c = RED)
      : key(value), parent(parent), left(left), right(right), color(c) {}

  // Destructor
  ~RBTreeNode() {}

  // Getters y Setters
  DataType getKey() const { return key; }

  RBTreeNode<DataType> *getParent() const { return parent; }
  RBTreeNode<DataType> *getLeft() const { return left; }
  RBTreeNode<DataType> *getRight() const { return right; }

  void setKey(DataType key) { this->key = key; }
  void setParent(RBTreeNode<DataType> *parent) { this->parent = parent; }
  void setLeft(RBTreeNode<DataType> *left) { this->left = left; }
  void setRight(RBTreeNode<DataType> *right) { this->right = right; }

 private:

  // Atributos
  DataType key;
  RBTreeNode<DataType> *parent = nullptr;
  RBTreeNode<DataType> *left = nullptr;
  RBTreeNode<DataType> *right = nullptr;
  enum colors color = RED;
};

template <typename DataType>
class RBTree {
 public:

  // Constructor y Destructor
  RBTree() {
    nil = new RBTreeNode<DataType>();
    nil->color = BLACK;
    nil->left = nil->right = nil->parent = nil;
    root = nil;
  }

  ~RBTree() {
    destroyTree(root);
    delete nil;
  }

  // Inserta un valor en el árbol
  void insert(const DataType &value) {

    if (root == nil) {
      root = new RBTreeNode<DataType>(value);
      root->left = root->right = root->parent = nil;
      root->color = BLACK;  // El nodo raíz siempre
    }
    
    RBTreeNode<DataType> *z = new RBTreeNode<DataType>(value);
    z->left = z->right = z->parent = nil;
    RBTreeNode<DataType> *y = nil;
    RBTreeNode<DataType> *x = root;

    while (x != nil) {
      y = x;
      if (z->key < x->key)
        x = x->left;
      else
        x = x->right;
    }
    z->parent = y;
    if (y == nil)
      root = z;
    else if (z->key < y->key)
      y->left = z;
    else
      y->right = z;

    z->left = nil;
    z->right = nil;
    z->color = RED;
    insertFixup(z);
  }

  // Borrar un valor en el árbol
  void remove(const DataType &value) {
    // Busca el nodo a eliminar
    RBTreeNode<DataType> *z = search(root, value);

    // Si no se encuentra, salir
    if (z == nil) return;

    // Preparar variables para la eliminación
    RBTreeNode<DataType> *y = z;
    RBTreeNode<DataType> *x;
    colors yOriginalColor = y->color;

    // Caso 1: z no tiene hijo izquierdo
    if (z->left == nil) {
        x = z->right;
        swap(z, z->right);  // Reemplazar z con su hijo derecho
    }
    // Caso 2: z no tiene hijo derecho
    else if (z->right == nil) {
        x = z->left;
        swap(z, z->left);  // Reemplazar z con su hijo izquierdo
    }
    // Caso 3: z tiene dos hijos
    else {
        y = getMinimum(z->right);  // Buscar sucesor
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            swap(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        swap(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;  // Mantener color original
    }

    // Eliminar el nodo z
    delete z;

    // Reparar propiedades del árbol si se eliminó un nodo negro
    if (yOriginalColor == BLACK)
        removeFixup(x);
}


  // Busca un valor en el árbol
  RBTreeNode<DataType> *search(const RBTreeNode<DataType> *node, const DataType &value) const {
    while (node != nil && node->key != value) {
      if (value < node->key)
        node = node->left;
      else
        node = node->right;
    }
    return const_cast<RBTreeNode<DataType> *>(node);
  }

  // Funciones auxiliares
  RBTreeNode<DataType> *getMinimum(const RBTreeNode<DataType> *node) const {
    while (node->left != nil) {
      node = node->left;
    }
    return const_cast<RBTreeNode<DataType> *>(node);
  }

  RBTreeNode<DataType> *getMaximum(const RBTreeNode<DataType> *node) const {
    while (node->right != nil) {
      node = node->right;
    }
    return const_cast<RBTreeNode<DataType> *>(node);
  }

  RBTreeNode<DataType> *getSuccessor(const RBTreeNode<DataType> *node) const {
    if (node->right != nil)
      return getMinimum(node->right);
    RBTreeNode<DataType> *y = node->parent;
    while (y != nil && node == y->right) {
      node = y;
      y = y->parent;
    }
    return y;
  }

  RBTreeNode<DataType> *getRoot() const { return root; }
  RBTreeNode<DataType> *getNil() const { return nil; }

  // Imprime el árbol en orden
  void inorderWalk() const {
    std::stack<RBTreeNode<DataType> *> stack;
    RBTreeNode<DataType> *current = root;
    while (current != nil || !stack.empty()) {
      while (current != nil) {
        stack.push(current);
        current = current->left;
      }
      current = stack.top();
      stack.pop();
      std::cout << current->key << " ";
      current = current->right;
    }
    std::cout << std::endl;
  }

 private:

  // Atributos
  RBTreeNode<DataType> *root;
  RBTreeNode<DataType> *nil;

  // Funciones auxiliares
  void destroyTree(RBTreeNode<DataType> *node) {
    if (node != nil) {
      destroyTree(node->left);
      destroyTree(node->right);
      delete node;
    }
  }

  void swap(RBTreeNode<DataType> *u, RBTreeNode<DataType> *v) {
    if (u->parent == nil)
      root = v;
    else if (u == u->parent->left)
      u->parent->left = v;
    else
      u->parent->right = v;
    v->parent = u->parent;
  }

  void insertFixup(RBTreeNode<DataType> *z) {
    while (z->parent->color == RED) {
      if (z->parent == z->parent->parent->left) {
        RBTreeNode<DataType> *y = z->parent->parent->right;
        if (y->color == RED) {
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else {
          if (z == z->parent->right) {
            z = z->parent;
            leftRotate(z);
          }
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          rightRotate(z->parent->parent);
        }
      } else {
        RBTreeNode<DataType> *y = z->parent->parent->left;
        if (y->color == RED) {
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else {
          if (z == z->parent->left) {
            z = z->parent;
            rightRotate(z);
          }
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          leftRotate(z->parent->parent);
        }
      }
    }
    root->color = BLACK;
  }

  void removeFixup(RBTreeNode<DataType> *x) {
    while (x != root && x->color == BLACK) {
      if (x == x->parent->left) {
        RBTreeNode<DataType> *w = x->parent->right;
        if (w->color == RED) {
          w->color = BLACK;
          x->parent->color = RED;
          leftRotate(x->parent);
          w = x->parent->right;
        }
        if (w->left->color == BLACK && w->right->color == BLACK) {
          w->color = RED;
          x = x->parent;
        } else {
          if (w->right->color == BLACK) {
            w->left->color = BLACK;
            w->color = RED;
            rightRotate(w);
            w = x->parent->right;
          }
          w->color = x->parent->color;
          x->parent->color = BLACK;
          w->right->color = BLACK;
          leftRotate(x->parent);
          x = root;
        }
      } else {
        RBTreeNode<DataType> *w = x->parent->left;
        if (w->color == RED) {
          w->color = BLACK;
          x->parent->color = RED;
          rightRotate(x->parent);
          w = x->parent->left;
        }
        if (w->right->color == BLACK && w->left->color == BLACK) {
          w->color = RED;
          x = x->parent;
        } else {
          if (w->left->color == BLACK) {
            w->right->color = BLACK;
            w->color = RED;
            leftRotate(w);
            w = x->parent->left;
          }
          w->color = x->parent->color;
          x->parent->color = BLACK;
          w->left->color = BLACK;
          rightRotate(x->parent);
          x = root;
        }
      }
    }
    x->color = BLACK;
  }

  void leftRotate(RBTreeNode<DataType> *x) {
    RBTreeNode<DataType> *y = x->right;
    x->right = y->left;
    if (y->left != nil)
      y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nil)
      root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
    y->left = x;
    x->parent = y;
  }

  void rightRotate(RBTreeNode<DataType> *x) {
    RBTreeNode<DataType> *y = x->left;
    x->left = y->right;
    if (y->right != nil)
      y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nil)
      root = y;
    else if (x == x->parent->right)
      x->parent->right = y;
    else
      x->parent->left = y;
    y->right = x;
    x->parent = y;
  }
};
