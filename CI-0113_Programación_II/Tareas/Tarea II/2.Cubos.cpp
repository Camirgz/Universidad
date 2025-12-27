#include <iostream>
#include <string>

#define MAX_JUEGOS 5
#define MAX_SUBJUEGOS 3
#define MAX_CARACTERES 200

using namespace std;

// Función split inspirada java
void split(const string &str, char divisor, string final[], int &tamanio) {
    tamanio = 0;  
    string temp = ""; 
    for (char ch : str) { 
        if (ch == divisor) {
            if (!temp.empty())  { 
                final[tamanio++] = temp;  
                temp = "";  
            }
        } else {
            temp += ch;  
        }
    }
    if (!temp.empty()) {
        final[tamanio++] = temp;  // Añadimos la última subcadena si existe
    }
    /*Recibe una cadena, un divisor y un arreglo de cadenas para almacenar los resultados.
    Itera sobre cada carácter de la cadena.
    Si el carácter es el divisor, añade la subcadena acumulada hasta ese punto al arreglo de resultados y reinicia la subcadena.
    Si el carácter no es el divisor, lo añade a la subcadena actual.
    Al final, añade la última subcadena al arreglo de resultados si no está vacía*/
}

// Función para calcular si el juego es posible 
bool esJuegoPosible(int juegos[MAX_JUEGOS][MAX_SUBJUEGOS][3], int juegoID, int maxRojos, int maxVerdes, int maxAzules) {
    int totalRojos = 0, totalVerdes = 0, totalAzules = 0; //Vars temporales

    for (int i = 0; i < MAX_SUBJUEGOS; ++i) {
        int rojos = juegos[juegoID][i][0];
        int verdes = juegos[juegoID][i][1];
        int azules = juegos[juegoID][i][2];

        totalRojos += rojos;
        totalVerdes += verdes;
        totalAzules += azules;

        if (totalRojos > maxRojos || totalVerdes > maxVerdes || totalAzules > maxAzules) {
            return false; // Si las cantidades totales exceden, el juego es imposible
        }
    }
    return true; 
    // Todos los conjuntos son posibles
}

// Función para analizar y extraer los valores de entrada
void procesarEntrada(const string &entrada, int juegos[MAX_JUEGOS][MAX_SUBJUEGOS][3], int juegoID) {
    string puntoycomaSplit[10], comaSplit[10], espacioSplit[10]; //Arreglos para almacenar temporalmente
    int pycTamanio = 0, comaTamanio = 0, espacioTamanio = 0;

    // Dividir el string por ";" para subjuegos de cada jugador
    split(entrada, ';', puntoycomaSplit, pycTamanio);

    // Procesar subjuego
    for (int i = 0; i < pycTamanio && i < MAX_SUBJUEGOS; i++) {

        // Dividir cada subjuego por ","
        split(puntoycomaSplit[i] /*subjuego*/, ',', comaSplit, comaTamanio);

        int conjuntoRojos = 0, conjuntoVerdes = 0, conjuntoAzules = 0; //contadores

        // Procesar cada subentrada
        for (int j = 0; j < comaTamanio; j++) {

            // Dividir por espacio para separar la cantidad del color
            split(comaSplit[j], ' ', espacioSplit, espacioTamanio);

            if (espacioTamanio == 2) {  // Comprobar que haya cantidad y color ("4 azul")
                int cantidad = stoi(espacioSplit[0]);  // Convertir la cantidad a entero (string to int(stoi))( el primer caracter es el numero)
                string color = espacioSplit[1];

                //Determinar a quién pertenece la cadena
                if (color == "azul" || color == "azules") {
                    conjuntoAzules += cantidad;  // Sumar la cantidad respectiva
                } else if (color == "rojo" || color == "rojos") {
                    conjuntoRojos += cantidad;
                } else if (color == "verde" || color == "verdes") {
                    conjuntoVerdes += cantidad;
                }
            } else {
                cout << "Formato inválido." << endl;
                return;
            }
        }

        // Añadir valores a listas
        juegos[juegoID][i][0] = conjuntoRojos;
        juegos[juegoID][i][1] = conjuntoVerdes;
        juegos[juegoID][i][2] = conjuntoAzules;
    }
}

int main() {

    //Valores máximos
    int maxRojos = 12;
    int maxVerdes = 13;
    int maxAzules = 14;

    int juegos[MAX_JUEGOS][MAX_SUBJUEGOS][3] = {0}; // Inicializar con ceros (3 = colores)
    int numJuegos = 0;
    int opcion;
    char entrada[MAX_CARACTERES];
    
    cout << "==Bienvenido al procesador de juegos==" << endl;
    //Menu
    do {
        cout << "\nMenú:" << endl;
        cout << "1. Añadir juego" << endl;
        cout << "2. Mostrar juegos" << endl;
        cout << "3. Calcular juegos válidos" << endl;
        cout << "4. Salir" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada para prevenir que se encicle

        switch (opcion) {
            case 1: {
                // Añadir un nuevo juego
                if (numJuegos < MAX_JUEGOS) {
                    cout << "Introduce los conjuntos del juego separados por punto y coma. Cada cantidad seguida del color, separados por coma." << endl;
                    cout << "Ejemplo: 3 azul, 4 rojo; 1 rojo, 2 verde, 6 azul; 2 verde" << endl;
                    cout << "Introduce los datos del juego: ";
                    cin.getline(entrada, MAX_CARACTERES);

                    procesarEntrada(entrada, juegos, numJuegos);
                    ++numJuegos;
                    cout << "Juego añadido exitosamente." << endl;
                } else {
                    cout << "Límite de juegos alcanzado." << endl;
                }
                break;
            }

            case 2: {
                // Mostrar todos los juegos
                for (int i = 0; i < numJuegos; ++i) {
                    cout << "Juego " << (i + 1) << ":" << endl;
                    for (int j = 0; j < MAX_SUBJUEGOS; ++j) {
                        cout << "Conjunto " << (j + 1) << ": ";
                        cout << juegos[i][j][0] << " rojos, " << juegos[i][j][1] << " verdes, " << juegos[i][j][2] << " azules" << endl;
                    }
                }
                break;
            }

            case 3: {
                // Calcular y mostrar juegos válidos
                int sumaIDPosibles = 0;
                
                for (int i = 0; i < numJuegos; ++i) {
                    if (esJuegoPosible(juegos, i, maxRojos, maxVerdes, maxAzules)) {
                        sumaIDPosibles += (i + 1);
                    }
                }
                
                cout << "La suma de los ID de los juegos posibles es: " << sumaIDPosibles << endl;
                break;
            }

            case 4:
                cout << "Saliendo del programa." << endl;
                break;

            default:
                cout << "Opción inválida." << endl;
        }

    } while (opcion != 4);

    return 0;
}
