#include "Platillo.h"

Platillo::Platillo() {
    id_cocinero = -1;
    nombre_platillo = "";
    tiempo_horneado = 0;
    urgente = false;
}

Platillo::Platillo(int id, string nombre, int tiempo, bool es_urgente) {
    id_cocinero = id;
    nombre_platillo = nombre;
    tiempo_horneado = tiempo;
    urgente = es_urgente;
}