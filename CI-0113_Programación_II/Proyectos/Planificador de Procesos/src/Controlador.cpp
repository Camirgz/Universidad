#include <iostream>
#include <string>  // Agregado para usar 'std::string'
#include "ListaProcesos.h"
#include "Controlador.h"
#include "RoundRobin.h"
#include "Prioridades.h"
#include "Proceso.h"
#include "Algoritmo.h" // Colores

using namespace std;

void Controlador::procesarConsulta()
{
    // Crear lista de procesos
    ListaProcesos<Proceso> lista;
    string entrada;  // Esto ahora funciona correctamente

    // Leer archivo
    cout << VERDE << "\n=== Bienvenido al Planificador de Procesos ===\n" << RESET;
    cout << "Ingrese el nombre de su archivo guardado en Files: ";
    getline(cin, entrada);
    string nombreArchivo = "files/" + entrada + ".txt";
    lista.leerArchivo(nombreArchivo);

    // Mostrar procesos
    if (lista.obtenerAbrirArchivo())
    {
        cout << "\n=== Procesos cargados ===\n";
        cout << "¿Cuál método quiere usar?\n1) Prioridad\n2) Round Robin\n3) Salir del programa\n" << endl;
        getline(cin, entrada);
        cout << endl;

        // Crear puntero a algoritmo
        Algoritmo *algoritmo = nullptr;

        // Menú de opciones
        if (entrada == "1")
        {
            lista.mostrarProcesos();
            algoritmo = new Prioridades();
        }
        else if (entrada == "2")
        {
            lista.mostrarProcesos();
            int quantum = 5; // Quantum predeterminado
            algoritmo = new RoundRobin(quantum);
        }
        else if (entrada == "3")
        {
            cout << "=== Saliendo ===\n";
        }
        else
        {
            cout << "Opción no válida.\n";
            return;
        }

        // Ejecutar algoritmo elegido con la lista de procesos a través de un método polimórfico
        algoritmo->ejecutar(lista.obtenerCabeza());

        // Liberar memoria
        delete algoritmo;
    }
    else // No se pudo abrir el archivo
    {
        cout << "No se cargaron procesos.\n";
        return;
    }

    cout << "\n === Gracias ===" << endl;
    cout << "\n" << endl;
    return;
}
