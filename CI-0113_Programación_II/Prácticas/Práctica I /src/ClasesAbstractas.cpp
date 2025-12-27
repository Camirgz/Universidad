#include <iostream>
#include <string>

using namespace std;

// Clase abstracta Pago
class Pago {
public:
    virtual void procesarPago() const = 0; // Método virtual puro
    virtual ~Pago() = default; // Destructor virtual por defecto
};

// Subclase PagoConTarjetaDeCrédito
class PagoConTarjetaDeCrédito : public Pago {
public:
    void procesarPago() const override {
        cout << "Procesando pago con tarjeta de crédito" << endl;
    }
};

// Subclase PagoConPaypal
class PagoConPaypal : public Pago {
public:
    void procesarPago() const override {
        cout << "Procesando pago con PayPal" << endl;
    }
};

// Subclase PagoEnEfectivo
class PagoEnEfectivo : public Pago {
public:
    void procesarPago() const override {
        cout << "Procesando pago en efectivo" << endl;
    }
};

// Función para finalizar la compra
void finalizarCompra(Pago* pagos[], int numPagos) { // Recibe un arreglo de punteros a Pago
    for (int i = 0; i < numPagos; ++i) {
        pagos[i]->procesarPago();
    }
}

// Función principal para probar la implementación
int main() {
    // Crear instancias de las subclases
    PagoConTarjetaDeCrédito pagoTarjeta;
    PagoConPaypal pagoPaypal;
    PagoEnEfectivo pagoEfectivo;

    // Crear un arreglo de punteros a Pago
    Pago* pagos[] = { &pagoTarjeta, &pagoPaypal, &pagoEfectivo };
    // Calcular el número de elementos del arreglo
    int numPagos = sizeof(pagos) / sizeof(pagos[0]);

    finalizarCompra(pagos, numPagos);

    return 0;
}