#ifndef ALGORITMO_H
#define ALGORITMO_H

#define MAGENTA "\033[35m"
#define ROJO "\033[31m"
#define AMARILLO "\033[33m"
#define VERDE "\033[32m"
#define CYAN "\033[36m"
#define AZUL "\033[34m"
#define RESET "\033[0m"

#include <iostream>
#include "Proceso.h"

/**
 * @brief Clase abstracta que representa un algoritmo.
 *        Define un método virtual puro que debe ser implementado por las clases derivadas.
 */
class Algoritmo {
public:
    /**
     * @brief Método virtual puro que ejecuta el algoritmo.
     *        Debe ser implementado en las clases derivadas.
     * 
     * @param cabeza Puntero al primer proceso en la lista.
     */
    virtual void ejecutar(Proceso* cabeza) = 0;

    /**
     * @brief Destructor virtual para permitir la correcta destrucción
     *        de objetos derivados al eliminar un objeto de tipo Algoritmo.
     */
    virtual ~Algoritmo() = default;

    /**
     * @brief Método que imprime los estados de los procesos.
     *        No es virtual, ya que puede usarse directamente en la clase base.
     * 
     * @param cabeza Puntero al primer proceso en la lista.
     */
    void imprimirEstados(Proceso* cabeza) {
        Proceso* actual = cabeza;
        std::cout << "\n=== Estado actual de los procesos: ===\n";
        while (actual) {
            std::cout << "Proceso: " << actual->nombre 
                      << " (Prioridad: " << actual->prioridad << ") (Estado: ";
            if (actual->estado == "Listo") {
                std::cout << AZUL << actual->estado << RESET;
            } else if (actual->estado == "Finalizado") {
                std::cout << VERDE << actual->estado << RESET;
            } else if (actual->estado == "Bloqueado por E/S") {
                std::cout << AMARILLO << actual->estado << RESET;
            } else if (actual->estado == "En ejecución: Activo") {
                std::cout << MAGENTA << actual->estado << RESET;
            } else {
                std::cout << actual->estado; // Sin color para otros estados
            }
            std::cout << ")\n";
            actual = actual->siguiente;
        }
    }
};

#endif
