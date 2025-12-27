#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "Contribuyente.h"

class Controlador {
private:
    Contribuyente* contribuyente;

public:
    Controlador(Contribuyente* c) : contribuyente(c) {}

    void procesarSalario(double salario) ;

    void procesarMovimiento(double monto) ;

    void reporte() ;
};

#endif
