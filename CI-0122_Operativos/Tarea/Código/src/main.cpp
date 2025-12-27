#include "Cocinero.h"
#include "Pasteleria.h"
#include "Platillo.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    cout << "========================================" << endl;
    cout << "  SIMULACIÓN: HORNO COMPARTIDO" << endl;
    cout << "  Pastelería Francesa" << endl;
    cout << "========================================" << endl;
    cout << endl;
    
    // Crear la pastelería (con 2 hornos)
    Pasteleria* pasteleria = new Pasteleria();
    
    // Crear platillos
    vector<Platillo> platillos;
    platillos.push_back(Platillo(1, "Croissant", 3, false));
    platillos.push_back(Platillo(2, "Pastel de emergencia", 2, true));
    platillos.push_back(Platillo(3, "Baguette", 4, false));
    platillos.push_back(Platillo(4, "Tarta urgente", 2, true));
    platillos.push_back(Platillo(5, "Macarons", 3, false));
    platillos.push_back(Platillo(6, "Éclair de emergencia", 2, true));
    
    // Crear cocineros
    vector<Cocinero*> cocineros;
    for (int i = 0; i < platillos.size(); i++) {
        cocineros.push_back(new Cocinero(platillos[i].id_cocinero, 
                                         platillos[i], 
                                         pasteleria));
    }
    
    // Iniciar todos los cocineros (threads)
    cout << "Iniciando cocineros..." << endl;
    cout << endl;
    for (int i = 0; i < cocineros.size(); i++) {
        cocineros[i]->iniciar();
    }
    
    // Esperar a que todos terminen
    for (int i = 0; i < cocineros.size(); i++) {
        cocineros[i]->esperar();
    }
    
    cout << endl;
    cout << "========================================" << endl;
    cout << "  Todos los platillos han sido horneados" << endl;
    cout << "========================================" << endl;
    
    // Limpiar memoria
    for (int i = 0; i < cocineros.size(); i++) {
        delete cocineros[i];
    }
    delete pasteleria;
    
    return 0;
}