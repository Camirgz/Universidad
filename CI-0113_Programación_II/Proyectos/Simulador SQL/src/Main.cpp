#include "../include/ConsultaSQL.h"
#include "../include/ListaRegistros.h"
#include <iostream>

using namespace std;

int main()
{
    ConsultaSQL consulta;

    // Leer la consulta SQL del usuario
    string entradaConsulta;
    cout << "===Bienvenido al simulador de SQL===" << endl;
    cout << "Ingrese su consulta SQL: ";
    getline(cin, entradaConsulta);

    // Procesar la consulta utilizando la clase ConsultaSQL
    consulta.procesarConsulta(entradaConsulta);
    cout << "\n ===Gracias===" << endl;

    return 0;
}
