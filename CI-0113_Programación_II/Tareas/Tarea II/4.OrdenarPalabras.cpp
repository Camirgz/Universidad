#include <iostream>

#define MAX_NODOS 10
#define MAX_PALABRA 100
#define MAX_DEFINICION 256

using namespace std;

struct Nodo {
    char palabra[MAX_PALABRA];
    char definicion[MAX_DEFINICION];

    Nodo(){}
    Nodo(char* p, char* d) {
        // Copiar palabra
        int i = 0;
        while (p[i] != '\0' && i < MAX_PALABRA - 1) {
            palabra[i] = p[i];
            ++i;
        }
        palabra[i] = '\0';

        // Copiar definición
        int j = 0;
        while (d[j] != '\0' && j < MAX_DEFINICION - 1) {
            definicion[j] = d[j];
            ++j;
        }
        definicion[j] = '\0';
    }
};

// Función para imprimir los nodos
void imprimirNodos(Nodo nodos[], int numNodos) {
    for (int i = 0; i < numNodos; ++i) {
        cout << nodos[i].palabra << ": " << nodos[i].definicion << endl;
    }
}

// Función de comparación para ordenar por palabra (de la A a la z)
bool compararPorPalabra(Nodo& a, Nodo& b) {
    int i = 0;
    while (a.palabra[i] != '\0' && b.palabra[i] != '\0') {
        if (a.palabra[i] > b.palabra[i]) return true;  // Orden descendente
        if (a.palabra[i] < b.palabra[i]) return false; // Orden ascendente
        ++i;
    }
    // Palabra más corta primero
    return a.palabra[i] != '\0' && b.palabra[i] == '\0';
}

// Función de orden
void ordenarNodos(Nodo nodos[], int numNodos) {
    for (int i = 0; i < numNodos - 1; ++i) {
        for (int j = 0; j < numNodos - i - 1; ++j) {
            if (compararPorPalabra(nodos[j], nodos[j + 1])) {
                // Intercambiar nodos[j] y nodos[j + 1]
                Nodo temp = nodos[j];
                nodos[j] = nodos[j + 1];
                nodos[j + 1] = temp;
            }
        }
    }
}

int main() {
    Nodo nodos[MAX_NODOS];
    int numNodos;

    cout << "Introduce el número de entradas de palabras (máximo " << MAX_NODOS << "): ";
    cin >> numNodos;
    cin.ignore(); // Limpiar el buffer de entrada para prevenir que se encicle

    if (numNodos > MAX_NODOS) {
        cout << "El número de entradas excede el máximo permitido. Se ajustará a " << MAX_NODOS << "." << endl;
        numNodos = MAX_NODOS;
    }

    for (int i = 0; i < numNodos; ++i) {
        cout << "\n====Entrada " << (i + 1)<<"===" << endl;

        cout << "Introduce la palabra: ";
        cin.getline(nodos[i].palabra, MAX_PALABRA);

        cout << "Introduce la definición: ";
        cin.getline(nodos[i].definicion, MAX_DEFINICION);
    }

    // Imprimir nodos antes de ordenar
    cout << "\n===Palabras y definiciones antes de ordenar:===" << endl;
    imprimirNodos(nodos, numNodos);

    // Ordenar los nodos por palabra en orden descendente
    ordenarNodos(nodos, numNodos);

    // Imprimir nodos después de ordenar
    cout << "\n===Palabras y definiciones después de ordenar (de A a Z):===" << endl;
    imprimirNodos(nodos, numNodos);

    return 0;
}
