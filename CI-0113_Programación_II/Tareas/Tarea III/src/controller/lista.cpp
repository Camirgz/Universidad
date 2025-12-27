#include <iostream>
#include <sstream>


#include "../include/nodo.h"

class Aja{
 public: 
   int x;
   Aja(int x) : x(x){ }
    
    std::string toString(){
        std::stringstream ss;
        ss << "Aja.x: " << x;
        return ss.str();
    }
    
    friend std::ostream& operator<< (std::ostream& os, Aja* aja){
        os << "Aja.x: " << aja->x;
        return os;
    }
};

template <typename T>
class Lista{
 public:
    Nodo<T>* front;
    Nodo<T>* end;
    Nodo<T>* popped;
      
    Lista(){
        front = NULL;
        end = front;
        popped = NULL;
    }
    
    Nodo<T>* append(T dato){
        Nodo<T>* nuevoNodo = new Nodo<T>(dato);
        if(end == NULL){
            front = nuevoNodo;
            end = nuevoNodo;
        }
        else{
            end->right = nuevoNodo;
            end = nuevoNodo;
        }
        return nuevoNodo;
    }
    
    std::string toString(){
        std::stringstream ss;
        ss << "Lista:\n";
        Nodo<T>* it = front;
        while(it != NULL){
            ss << "Dato: " << it->dato << "\n";
            it = it->right;
        }
        ss << "----------------------------\n";
        
        return ss.str();
    }
    
    friend std::ostream& operator<< (std::ostream& os, Lista<T>& l){
        os << l.toString();
        return os;
    }
    
    ~Lista(){
        Nodo<T>* it = front;
        while(it != NULL){
            Nodo<T>* sacar = front;
            front = front->right;
            sacar->right = NULL;
            delete sacar;
             it = it->right;
        }
        
        it = popped;
        while(it != NULL){
            Nodo<T>* sacar = front;
            front = front->right;
            sacar->right = NULL;
            delete sacar;
             it = it->right;
        }
    }
};

int main(){
    Lista<int> miLista;
    miLista.append(5);
    miLista.append(3);
    miLista.append(2);
    
    std::cout << miLista << std::endl;
    
    
    Lista<Aja*> ajas;
    ajas.append(new Aja(55));
    ajas.append(new Aja(33));
    ajas.append(new Aja(22));
    
    std::cout << ajas << std::endl;

    return 0;
}