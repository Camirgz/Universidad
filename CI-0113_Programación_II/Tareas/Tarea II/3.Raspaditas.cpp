#include <iostream>
#include <string>

using namespace std;

const int MAX_NUMS = 100; // Ideal

// Split Java con parámetros, usado tmb en ejercicio 2
void split(const string &str, char divisor, string final[], int &tamanio) {
    tamanio = 0;
    string temp = "";
    for (char ch : str) {
        if (ch == divisor) {
            if (!temp.empty()) {
                final[tamanio++] = temp;
                temp = "";
            }
        } else {
            temp += ch;
        }
    }
    if (!temp.empty()) {
        final[tamanio++] = temp;
    }
}

// Función para calcular los puntos de una raspa
int calcularPuntos(const string ganadores[], int sizeGanadores, const string nuestros[], int sizeNuestros) {
    int puntos = 0; //Setear en 0 cada vez que se llama el método

    for (int i = 0; i < sizeNuestros; ++i) {//doble ciclo para comparar
        bool encontrado = false;
        for (int j = 0; j < sizeGanadores; ++j) {
            if (nuestros[i] == ganadores[j]) {
                if (!encontrado) {
                    puntos += 1;
                    encontrado = true;
                }
            }
        }
    }
    return puntos*2; //Duplicación
}

int main() {
    string input;
    int totalPuntos = 0;
    int numeroRaspaditas = 1;
    cout<<"==Bienvenido=="<<endl;
    while (true) {
        cout << "Introduce la raspadita(o 'fin' para terminar): ";
        getline(cin, input); //Entrada

        if (input == "fin") {
            break;
        }

        // Arrays para almacenar los números ganadores y nuestros números
        string partes[2];
        int tamanioPartes; //Variable para usar dentro del método
        split(input, '|', partes, tamanioPartes);

        if (tamanioPartes != 2) {
            cout << "==Error: La entrada debe contener exactamente una barra vertical (|)==" << endl;
            continue;
        }

        string numerosGanadores[MAX_NUMS];
        string numerosNuestros[MAX_NUMS];
        int sizeGanadores, sizeNuestros;//tamaños

        split(partes[0], ' ', numerosGanadores, sizeGanadores);
        split(partes[1], ' ', numerosNuestros, sizeNuestros);

        // Calcular los puntos para la raspadita
        int puntos = calcularPuntos(numerosGanadores, sizeGanadores, numerosNuestros, sizeNuestros);
        totalPuntos += puntos;

        // Mostrar el resultado
        cout<<"====="<<endl;
        cout << "La tarjeta " << numeroRaspaditas++ << " tiene " 
             << sizeGanadores << " números ganadores ("
             << partes[0] << "), por lo que vale " << puntos << " puntos." << endl;
        cout<<"===="<<endl;
    }

    // Mostrar el total de puntos
    cout << "==Total de puntos: " << totalPuntos <<"=="<< endl;

    return 0;
}
