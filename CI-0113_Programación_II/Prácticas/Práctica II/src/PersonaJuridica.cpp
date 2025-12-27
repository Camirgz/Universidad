#include "Contribuyente.cpp"
#include <iostream>
using namespace std;

class PersonaJuridica : public Contribuyente {
    public:
        double* impuesto = new double;
        double ingresos = utilidades;

    void calcularImpuesto() const override { //Método virtual polimórfico

        // Cálculo de impuestos para Persona Jurídica
        if (ingresos <= 4181000) {
            *impuesto = 0;
        } else if (ingresos <= 6244000) {
            *impuesto = (ingresos - 4181000) * 0.15;
        } else if (ingresos <= 10414000) {
            *impuesto = (6244000 - 4181000) * 0.15 + (ingresos - 6244000) * 0.20;
        } else {
            *impuesto = (6244000 - 4181000) * 0.15 + (10414000 - 6244000) * 0.20 + (ingresos - 10414000) * 0.25;
        }
    }

    void reporte() override { //Método virtual polimórfico
        Contribuyente::reporte();
        cout << "Persona Física" << endl;
        cout << "Impuesto a pagar: " << *impuesto << endl;
        cout << "Porcentaje de impuesto sobre utilidades: " << (*impuesto / ingresos) * 100 << "%" << endl;
    }
};