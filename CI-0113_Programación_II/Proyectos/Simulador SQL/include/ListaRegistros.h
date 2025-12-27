#ifndef LISTAREGISTROS_H
#define LISTAREGISTROS_H

#include "Registro.h"
#include <fstream>
#include <sstream>

using namespace std;

class ListaRegistros {
public:
    Registro *cabeza;
    int numFilas;

    ListaRegistros() : cabeza(nullptr) {};
    void leerArchivoCSV(const string &rutaArchivo);
    void imprimirLista(int numcolumnas, string *columnas, bool imprimirTodas) const;
    string* getColumna(string columna, bool* hola) const;
    string* getFila(int fila) const;
    string* getFila(string valor) const;

};

#endif // LISTAREGISTROS_H
