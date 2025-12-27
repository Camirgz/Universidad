#include "Contribuyente.cpp"
#include <iostream>
using namespace std;

class PersonaFisica : public Contribuyente {
    public:
        double* impuesto = new double;
        double ingresos = utilidades;

    void calcularImpuesto() const override {
        // Cálculo de impuestos
        if (ingresos <= 4181000) { // Tramo 1
            *impuesto = 0;
        } else if (ingresos <= 6244000) { // Tramo 2
            *impuesto = (ingresos - 4181000) * 0.10;
        } else if (ingresos <= 10414000) { // Tramo 3
            *impuesto = (6244000 - 4181000) * 0.10 + (ingresos - 6244000) * 0.15;
        } else { // Tramo 4
            *impuesto = (6244000 - 4181000) * 0.10 + 
            (10414000 - 6244000) * 0.15 + (ingresos - 10414000) * 0.20; // Tramo 5
        }
    }

    void reporte() override { 
        Contribuyente::reporte();
        cout << "Persona Física" << endl;
        cout << "Impuesto a pagar: " << *impuesto << endl;
        cout << "Porcentaje de impuesto sobre utilidades: " <<
         (*impuesto / ingresos) * 100 << "%" << endl;
    }

    ~PersonaFisica() {
        delete impuesto;
    }

};