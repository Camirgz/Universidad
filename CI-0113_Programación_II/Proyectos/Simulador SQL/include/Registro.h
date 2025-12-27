#ifndef REGISTRO_H
#define REGISTRO_H

#include <iostream>
#include <string>

using namespace std;

class Registro { 
    public:
        int numColumnas;          // Número de columnas
        string* valores;     // Arreglo dinámico para almacenar los valores de cada columna
        Registro* siguiente;      // Puntero al siguiente nodo (lista simple)

        // Constructor para inicializar el registro con el número de columnas
        Registro(int columnas) : numColumnas(columnas), siguiente(nullptr) {
            valores = new string[columnas];  // Arreglo dinámico de strings
        }

        // Destructor para liberar la memoria
        ~Registro() {
            delete[] valores;
        }

        // Método para imprimir el registro
        void imprimir() const {
            for (int i = 0; i < numColumnas; ++i) {
                cout << valores[i];
                if (i < numColumnas - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        void imprimir(int columna) const {
            bool hola = true;
            for (int i = 0; i < numColumnas and hola; ++i) {
                // if valores[i] == columna(id)
                if ( i == columna) {
                    cout << valores[i] <<endl;
                    hola = false;
                }
                
            }
        }
};


#endif
