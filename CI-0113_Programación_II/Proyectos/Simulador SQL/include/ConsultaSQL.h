#ifndef CONSULTA_SQL_H
#define CONSULTA_SQL_H

#include <iostream>
#include <string>

#include "Registro.h"
#include "ListaRegistros.h"

using namespace std;

class ConsultaSQL {
public:
    static const int MAX_COLUMNAS = 100;
    string archivo;                  // Nombre del archivo extraído de la consulta (con la ruta completa)
    string columnas[15];             // Arreglo para almacenar hasta 10 columnas
    int numColumnas;                 // Número de columnas seleccionadas
    bool seleccionarTodas; 
    ListaRegistros lista;

    
    ConsultaSQL();

    void procesarConsulta(const string& consulta);
    bool consulta();
    string* procesarDistinct(const string* columna, int& sizeDistinct) const;
    double getMin(const string* columna);
    void recorrer() const;
    double getMax(const string* columna);
    void extraerColumnas(const string columnasStr);
    double getSum(const string* columna);
    bool soloSelect(const string& consulta);
    void procesarWhere(const string& columna, const string& parametro);
    void imprimirJsonFilas(string* fila) const;
    void imprimirJsonFilas(string* fila, int numColumnas, string nombre) const;
    void imprimirJsonColumnas(string* columna, string nombre) const;
    void imprimirJson() const;
    void procesarOrderBy(string orden) const;
};

#include <algorithm> 
//SOLO PARA SWAP
//SWAP: Intercambiar valores de dos variables
    // var1 var2 varAux
    // varAux=Var1
    // var1=var2
    // var2=varAux

#endif // CONSULTA_SQL_H
