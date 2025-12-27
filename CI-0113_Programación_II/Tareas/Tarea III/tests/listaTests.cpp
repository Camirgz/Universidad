#include "tests.h"
#include <lista.cpp>
#include <iostream>

using namespace std;

int main(){

    // Casos de prueba:
    int casoPrueba1 = 5;
    int casoPrueba2 = 3;
    int casoPrueba3 = 2;

    Lista<int> ebp;

    Nodo<int>* resultadoReal = ebp.append(casoPrueba1);
    assertEquals(casoPrueba1, resultadoReal->dato, "Caso 1");

    resultadoReal = ebp.append(casoPrueba2);
    assertEquals(casoPrueba2, resultadoReal->dato, "Caso 2");

    resultadoReal = ebp.append(casoPrueba3);
    assertEquals(casoPrueba3, resultadoReal->dato, "Caso 3");

    return 0;
}





