#include <iostream>
using namespace std;

#define MAX_entradas 100
#define LONGITUD_MAX 100

// Función para calcular la calibración de una entrada
int obtenerCalibracion(char* entrada) {
    char primerDigito = '\0';
    char ultimoDigito = '\0'; //              '\0' =  final de la cadena

    // Encontrar el primer dígito
    for (int i = 0; entrada[i] != '\0'; ++i) {
        if (entrada[i] >= '0' && entrada[i] <= '9') {  // Verificar si es un dígito
            primerDigito = entrada[i]; 
            break; //Termina cuando encuentra el primero
        }
    }

    // Encontrar el último dígito
    for (int i = 0; entrada[i] != '\0'; ++i) {
        if (entrada[i] >= '0' && entrada[i] <= '9') {
            ultimoDigito = entrada[i];
        } //Va cambiando "el primero" 
    }

    // Si se encontraron ambos dígitos, combinar para formar el número de dos dígitos
    if (primerDigito != '\0' && ultimoDigito != '\0') {
        int numeroCalibrado = (primerDigito - '0') * 10 + (ultimoDigito - '0'); //Fórmula
        return numeroCalibrado;
    }

    return 0;
}

int main() {
    char entradas[MAX_entradas][LONGITUD_MAX];
    int numEntradas = 0;
    int opcion;
    int sumaTotal = 0;

    cout << "--- Bienvenido al programa de calibración ---" << endl;

    do {
        //Menú
        cout << "\n===Menú:====" << endl;
        cout << "1. Añadir entrada" << endl;
        cout << "2. Mostrar entradas" << endl;
        cout << "3. Realizar calibraciones" << endl;
        cout << "4. Reiniciar entradas" << endl;
        cout << "5. Salir" << endl;
        cout << "==Selecciona una opción:== ";
        cin >> opcion; //Solo cin porque es solo un caracter el que espera recibir
        cin.ignore(); // Limpiar el buffer de entrada para evitar que se encicle

        //Manejo entradas menú

        switch (opcion) {
            case 1:
                if (numEntradas < MAX_entradas) {
                    cout << "Ingrese una entrada: ";
                    cin.getline(entradas[numEntradas], LONGITUD_MAX);//Get line para varios caracteres
                    ++numEntradas;
                } else {
                    cout << "Supera el límite de entradas." << endl;
                }
                break;

            case 2:
                cout << "Entradas almacenadas:" << endl;
                for (int i = 0; i < numEntradas; ++i) {
                    cout << i + 1 << ". " << entradas[i] << endl;
                }
                break;
            
            case 3:
                sumaTotal = 0; // Reiniciar suma total para nuevas calibraciones
                for (int i = 0; i < numEntradas; ++i) {
                    int calibracion = obtenerCalibracion(entradas[i]);
                    cout << "Calibración para la entrada '" << entradas[i] << "': " << calibracion << endl;
                    sumaTotal += calibracion;
                }
                cout << "Suma total de valores de calibración: " << sumaTotal << endl;
                break;

            case 4:
                numEntradas = 0; // Reiniciar el contador de entradas
                cout << "Las entradas han sido reiniciadas." << endl;
                break;

            case 5:
                cout << "=== Gracias! ===" << endl;
                break;

            default:
                cout << "Opción inválida." << endl;
        }

    } while (opcion != 5); //Fin do-while

    return 0;
}
