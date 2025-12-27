//Nodo de la lista de procesos
#include "Proceso.h"

// Constructor
Proceso::Proceso(const string& nombre, int prioridad) {
    this->nombre = nombre;  //this porque no sabe que nombre es
    this->prioridad = prioridad;
    instrucciones = "";
    siguiente = nullptr;
    estado = "Listo";
}
    

