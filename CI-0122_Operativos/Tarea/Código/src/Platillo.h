#ifndef PLATILLO_H
#define PLATILLO_H

#include <string>
using namespace std;

class Platillo {
public:
    int id_cocinero;
    string nombre_platillo;
    int tiempo_horneado;  // en segundos para la simulación
    bool urgente;
    
    Platillo();
    Platillo(int id, string nombre, int tiempo, bool es_urgente);
};

#endif