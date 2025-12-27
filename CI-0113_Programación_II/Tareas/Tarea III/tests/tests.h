
#include <iostream>
using namespace std;

// Color Terminal Output Library
// MIT Licensed Library

// There are 6 colors:
//
// blue
// green
// cyan
// red
// magenta
// yellow

// Usage:
// color("red", "Error occured", true);
//       color  text           newLine

void color(string color, string line, bool newLine = false);

bool assertEquals(string resultadoEsperado, string resultadoReal, string nombrePrueba);

bool assertEquals(int resultadoEsperado, int resultadoReal, string nombrePrueba);

bool assertEquals(int resultadoEsperado[], int resultadoReal[], int n);
