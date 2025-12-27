#include "tests.h"
#include "../src/controller/arbol.cpp"
#include <iostream>
#include <sstream>

using namespace std;

/*
g++ -c tests.cpp -o tests.o
g++ -I"../include" -I"../src/controller" -L"../lib/dynamic" tests.o arbolTests.cpp -o arbolTests -lp2ds
*/

int main() {
    ArbolB<int> ebp;

    // Inserción de datos en el árbol
    ebp.insertar(34);
    ebp.insertar(78);
    ebp.insertar(20);
    ebp.insertar(99);
    ebp.insertar(1);
    ebp.insertar(77);
    ebp.insertar(25);

    // Caso 1: Imprimir el árbol después de insertar los datos
    stringstream ss;
    ebp.imprimir(ebp.root, ss);
    string resultadoReal = ss.str();
    string resultadoEsperado = "1 20 25 34 77 78 99";
    assertEquals(resultadoEsperado, resultadoReal, "Caso 1");

    // Caso 2: Eliminar el nodo con el dato 20 y verificar el árbol
    ebp.eliminar(ebp.root, 20);
    ss.str(""); // Limpiar el stringstream para reutilizarlo
    ebp.imprimir(ebp.root, ss);
    string resultadoReal2 = ss.str();
    string resultadoEsperado2 = "1 25 34 77 78 99";
    assertEquals(resultadoEsperado2, resultadoReal2, "Caso 2");

    return 0;
};
