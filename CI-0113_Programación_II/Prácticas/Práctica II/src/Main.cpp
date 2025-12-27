#include <iostream>
#include "Contribuyente.h"
#include "PersonaFisica.h"
#include "PersonaJuridica.h"
#include "Controlador.h"

using namespace std;

int main() {
    int tipoContribuyente;
    cout << "==Bienvenido al sistema de impuestos==" << endl;
    cout << "Seleccione el tipo de contribuyente \n 1 - Persona Física \n 2 - Persona Jurídica: ";
    cin >> tipoContribuyente;

    Contribuyente* contribuyente = nullptr; 

    if (tipoContribuyente == 1) {
        contribuyente = new PersonaFisica();
    } else if (tipoContribuyente == 2) {
        contribuyente = new PersonaJuridica();
    } else {
        cout << "Tipo de contribuyente inválido." << endl;
        return 1;
    }

    Controlador controlador(contribuyente);
    int opcion;

    do {
        cout << "Seleccione una opción:\n1. Procesar Salario\n2. Procesar Movimiento\n3. Generar Reporte\n4. Salir\nOpción: ";
        cin >> opcion;

        if (opcion == 1) {
            double salario;
            cout << "Ingrese el salario: ";
            cin >> salario;
            controlador.procesarSalario(salario);
        } else if (opcion == 2) {
            double movimiento;
            cout << "Ingrese el movimiento (positivo para ingresos, negativo para egresos): ";
            cin >> movimiento;
            controlador.procesarMovimiento(movimiento);
        } else if (opcion == 3) {
            controlador.reporte();
        } else if (opcion != 4) {
            cout << "Opción inválida." << endl;
        }
    } while (opcion != 4);

    delete contribuyente; // Liberar memoria
    return 0;
}
