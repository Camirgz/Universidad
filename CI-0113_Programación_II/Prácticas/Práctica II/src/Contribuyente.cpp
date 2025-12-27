#include <iostream>
#include <string>

using namespace std;

class Contribuyente {
    
    public:
    
    double utilidades;
    double salario;

    //Getter
    double getUtilidades() const {
        return utilidades;
    }

    double getSalario() const {
        return salario;
    }

    // Metodos
    void agregarMovimiento(double monto) {
        if(monto != 0){
            utilidades += monto;
            cout << "Movimiento agregado" << endl;
        }
        else{
            cout << "No se puede agregar un movimiento de 0" << endl;
        }
    }

    void agregarSalario(double monto) {
        if(monto != 0){
            salario += monto;
            cout << "Salario agregado" << endl;
        }
        else{
            cout << "No se puede agregar un salario de 0" << endl;
        }
    }

    virtual void reporte() {
        cout << "Utilidades: " << utilidades << endl;
    }

    virtual void calcularImpuesto() const = 0;

    // Destructor virtual por defecto
    virtual ~Contribuyente();
};