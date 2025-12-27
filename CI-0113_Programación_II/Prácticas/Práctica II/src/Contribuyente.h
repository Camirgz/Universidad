#ifndef CONTRIBUYENTE_H
#define CONTRIBUYENTE_H

#include <iostream>

class Contribuyente {
public:
    double utilidades;
    double salario;

    // Métodos getters
    double getUtilidades() const;

    double getSalario() const ;

    // Métodos para movimientos y salario
    void agregarMovimiento(double monto) ;

    void agregarSalario(double monto) ;

    virtual void reporte() ;

    virtual void calcularImpuesto() const = 0;

    // Destructor virtual
    virtual ~Contribuyente() {}
};

#endif
