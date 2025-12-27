#ifndef PROCESO_H
#define PROCESO_H

#include <string>
using namespace std;

// Estructura Proceso
class Proceso
{
public:
    // Atributos
    /**
     * @brief  nombre del proceso
     * @brief  prioridad del proceso
     * @brief  instrucciones a ejecutar del proceso}
     * @brief  siguiente proceso en la lista
     * @brief  estado del proceso
     * 
     */

    // Atributos
    string nombre;
    int prioridad;
    string instrucciones;
    Proceso *siguiente;
    string estado;

    // Constructor
    /**
     * @brief Construct a new Proceso object
     * 
     * @param nombre_  nombre del proceso
     * @param prioridad_  prioridad a ejecutar del proceso
     */
    Proceso(const string &nombre_, int prioridad_);
};

#endif
