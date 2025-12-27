#include "Controlador.hpp"
#include <iostream>

using namespace std;

int main() {

    Controlador controlador; // Crear instancia del controlador
    cout << " ----------------- Pruebas Estructuras de Datos ----------------- " << endl;

    cout << "\n====== Lista Enlazada Simple ====== " << endl;
    controlador.insercionAleatoria();
    controlador.busquedaAleatoria();
    controlador.eliminacionAleatoria();
    
    controlador.insercionOrdenada();
    controlador.busquedaOrdenada();
    controlador.eliminacionOrdenada();

    cout << "\n====== Árbol de Búsqueda Binaria ====== " << endl;
    controlador.insercionAleatoriaABB();
    controlador.busquedaAleatoriaABB();
    controlador.eliminacionAleatoriaABB();  

    controlador.insercionOrdenadaABB();
    controlador.busquedaOrdenadaABB();
    controlador.eliminacionOrdenadaABB();  

    cout << "\n====== Tabla Hash Encadenada ====== " << endl;
    controlador.insercionAleatoriaCHT();
    controlador.busquedaAleatoriaCHT();
    controlador.eliminacionAleatoriaCHT();

    controlador.insercionOrdenadaCHT();
    controlador.busquedaOrdenadaCHT();
    controlador.eliminacionOrdenadaCHT();
    
    cout << "\n====== Árbol Rojo-Negro ====== " << endl;
    controlador.insercionAleatoriaRBT();
    controlador.busquedaAleatoriaRBT();
    controlador.eliminacionAleatoriaRBT();

    controlador.insercionOrdenadaRBT();
    controlador.busquedaOrdenadaRBT();
    controlador.eliminacionOrdenadaRBT();

    return 0;
}