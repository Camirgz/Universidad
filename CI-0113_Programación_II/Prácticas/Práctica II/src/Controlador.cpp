#include <iostream>
#include "Contribuyente.cpp"

class Controlador {
public: 
    Contribuyente* contribuyente;
    Controlador(Contribuyente* c) : contribuyente(c) {}

    void procesarSalario(double salario) {
        if (salario > 0) {
            contribuyente->agregarMovimiento(salario);
            contribuyente->calcularImpuesto();
        } else {
            cout << "Salario inválido." << endl;
        }
    }

    void procesarMovimiento(double monto) {
        contribuyente->agregarMovimiento(monto);
    }

    void reporte() {
        contribuyente->reporte();
    }
};
