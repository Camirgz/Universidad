#ifndef PERSONAFISICA_H
#define PERSONAFISICA_H

#include "Contribuyente.h"

class PersonaFisica : public Contribuyente {
public:
    double* impuesto;

    PersonaFisica() : impuesto(new double(0)) {}

    void calcularImpuesto() const override ;

    void reporte() override ;

    ~PersonaFisica() ;
};

#endif
