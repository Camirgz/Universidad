#include <iostream>
#include <string>

using namespace std;

const int TAM_MAXIMO = 100; // ideal

void transmutar_ak(string entrada[], int tamano) {
    string resultado[TAM_MAXIMO] = { " " }; 
    bool transmutado[TAM_MAXIMO] = { false }; // Marcar celdas transmutadas
    int indice = 0;

    for (int i = 0; i < tamano; ++i) {
        if (i < tamano - 1 && entrada[i] == entrada[i + 1] && !transmutado[i] && !transmutado[i + 1]) {
            // Transmutar
            char siguiente_letra = entrada[i][0] + 1; // Siguiente letra
            resultado[indice++] = string(1, siguiente_letra);
            transmutado[i] = true;
            transmutado[i + 1] = true;
            i++; 
        } else if (!transmutado[i]) {
            resultado[indice++] = entrada[i];
        }
    }

    // Reorganizar letras al inicio
    string resultado_final[TAM_MAXIMO] = { " " };
    for (int i = 0; i < indice; ++i) {
        resultado_final[i] = resultado[i];
    }

    // Imprimir lista vacía
    if (indice == 0) {
        cout << "resultado: []" << endl;
        return;
    }

    // Resultado final
    cout << "resultado: [";
    for (int i = 0; i < tamano; ++i) {
        if (resultado_final[i] != " ") {
            cout << resultado_final[i];
            if (i < tamano - 1) {
                cout << ", ";
            }
        }
    }
    cout << "]" << endl;
}

int main() {
    string entrada[TAM_MAXIMO];
    int tamano;

    cout << "Ingrese el número de elementos (máximo " << TAM_MAXIMO << "): ";
    cin >> tamano;

    cout << "Ingrese los elementos (letras de 'a' a 'k' o espacios):" << endl;
    for (int i = 0; i < tamano; ++i) {
        cin >> entrada[i];
    }

    transmutar_ak(entrada, tamano);

    return 0;
}
