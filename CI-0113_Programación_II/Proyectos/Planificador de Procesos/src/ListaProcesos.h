#ifndef LISTA_PROCESOS_H
#define LISTA_PROCESOS_H

// Includes
#include <unistd.h> // Para sleep() en sistemas UNIX/Linux
#include <string>
#include "Proceso.h"

// Clase ListaProcesos - Template
/**
 * @brief lista de procesos implementada con plantillas
 * 
 * @tparam T 
 */

template <typename T>
class ListaProcesos {

    // Atributos
private:
    // Puntero a la cabeza de la lista
    T* cabeza;
    bool abrirArchivo;

    // Métodos
public:
    /**
     * @brief Construct a new Lista Procesos object
     * 
     */
    ListaProcesos();
    /**
     * @brief metodo que obtiene si se abrio el archivo
     * 
     * @return true  si se abrio el archivo
     * @return false  si no se abrio el archivo
     */
    bool obtenerAbrirArchivo() const;

    /**
     * @brief metodo que agrega un elemento a la lista
     * 
     * @param nombre  nombre del proceso
     * @param prioridad  prioridad del proceso
     * @param instrucciones  instrucciones a ejecutar del proceso
     */
    void agregarElemento(const std::string& nombre, int prioridad, const std::string& instrucciones);

    /**
     * @brief metodo que muestra los elementos de la lista
     * 
     */
    void mostrarElementos() const;

    /**
     * @brief metodo que muestra los procesos de la lista
     * 
     */
    void mostrarProcesos() const; // Cambiado de mostrarElementos a mostrarProcesos

    /**
     * @brief metodo que lee un archivo de texto con los elementos
     * 
     * @param nombreArchivo  nombre del archivo a leer
     */
    void leerArchivo(const std::string& nombreArchivo);
    
    /**
     * @brief metodo que elimina la lista
     * 
     */
    void eliminarLista();

    /**
     * @brief metodo que obtiene la cabeza de la lista
     * 
     * @return T*  puntero a la cabeza de la lista
     */
    ~ListaProcesos();

    /**
     * @brief   metodo que obtiene la cabeza de la lista
     * 
     * @return T*   puntero a la cabeza de la lista
     */
    T* obtenerCabeza() const;
};

#endif // LISTA_PROCESOS_H
