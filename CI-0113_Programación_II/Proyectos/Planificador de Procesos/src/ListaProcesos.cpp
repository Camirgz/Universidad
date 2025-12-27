#include "ListaProcesos.h"
#include <iostream>
#include <fstream>
using namespace std;

// Es necesario instanciar las plantillas (templates) fuera de este archivo
template class ListaProcesos<Proceso>; // Instancia de la clase para Proceso

// Constructor
template <typename T>
ListaProcesos<T>::ListaProcesos() : cabeza(nullptr), abrirArchivo(false) {}

// Agregar un elemento a la lista
template <typename T>
void ListaProcesos<T>::agregarElemento(const string& nombre, int prioridad, const string& instrucciones) {
    // Crear un nuevo elemento
    T* nuevo = new T(nombre, prioridad);
    nuevo->instrucciones = instrucciones;

    // Agregar el elemento a la lista
    if (!cabeza) {
        cabeza = nuevo;
    } else {
        T* actual = cabeza;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

// Mostrar los procesos de la lista
template <typename T>
void ListaProcesos<T>::mostrarProcesos() const {  // Método corregido
    cout << "=== Elementos cargados ===\n";
    T* actual = cabeza;
    while (actual) {
        cout << "Nombre del Elemento: " << actual->nombre << "\n";
        cout << "Prioridad: " << actual->prioridad << "\n";
        cout << "Instrucciones:\n" << actual->instrucciones << "\n\n";
        actual = actual->siguiente;
    }
}

// Leer un archivo de texto con los elementos
template <typename T>
void ListaProcesos<T>::leerArchivo(const string& nombreArchivo) {
    // Abrir el archivo
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo.\n";
        abrirArchivo = false;
        return;
    }

    // Leer el archivo línea por línea
    string linea;
    string nombreElemento;
    int prioridad = 0;
    string instrucciones = "";
    bool leyendoElemento = false;

    // Leer el archivo línea por línea
    while (getline(archivo, linea)) {
        if (linea.find("proceso") == 0) {
            if (leyendoElemento) {
                agregarElemento(nombreElemento, prioridad, instrucciones);
                instrucciones.clear();
            }
            leyendoElemento = true;
            size_t pos1 = linea.find(" ");
            size_t pos2 = linea.rfind(" ");
            nombreElemento = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            prioridad = stoi(linea.substr(pos2 + 1));
        } else if (linea == "fin proceso") {
            agregarElemento(nombreElemento, prioridad, instrucciones);
            instrucciones.clear();
            leyendoElemento = false;
        } else {
            instrucciones += linea + "\n";
        }
    }
    abrirArchivo = true;
    archivo.close();
}

// Eliminar la lista de elementos
template <typename T>
void ListaProcesos<T>::eliminarLista() {
    while (cabeza) {
        T* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

// Obtener la cabeza de la lista
template <typename T>
T* ListaProcesos<T>::obtenerCabeza() const {
    return cabeza;
}

// Destructor
template <typename T>
ListaProcesos<T>::~ListaProcesos() {
    while (cabeza) {
        T* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

template <typename T>
bool ListaProcesos<T>::obtenerAbrirArchivo() const {
    return abrirArchivo;
}
