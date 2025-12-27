// Clase para procesar una consulta SQL y extraer información de un archivo CSV
#include "../include/ConsultaSQL.h"
using namespace std;

// Constructor
ConsultaSQL::ConsultaSQL() : numColumnas(0), seleccionarTodas(false) {}

// Método para procesar la consulta SQL
void ConsultaSQL::procesarConsulta(const string& consulta) {
    
    // Variables de búsqueda de palabras clave en la consulta
    size_t posSelect = consulta.find("SELECT");
    size_t posFrom = consulta.find(" FROM ");
    size_t endPosCSV = consulta.find(".csv", posFrom) + 4; 
    size_t posDistinct = consulta.find("SELECT DISTINCT");
    size_t posMin = consulta.find("SELECT MIN");
    size_t posMax = consulta.find("SELECT MAX");
    size_t posCount = consulta.find("SELECT COUNT");
    size_t posSum = consulta.find("SELECT SUM");
    size_t posAvg = consulta.find("SELECT AVG");
    size_t posWhere = consulta.find("WHERE");
    size_t posOrderBy = consulta.find("ORDER BY");

    bool existeColumna;
    string comando;

    // Variables para almacenar las columnas y el archivo y validar la consulta
    string columnasStr = "";
    if (posSelect == string::npos || posFrom == string::npos) {
        cerr << "Error: La consulta SQL no es válida." << endl;
        return;
    }

    // Extraer el nombre del archivo CSV
    string archivoStr = consulta.substr(posFrom + 6, endPosCSV - (posFrom + 6));
    archivo = "../db/" + archivoStr;
    cout << "\nArchivo: " << archivo << endl;
    lista.leerArchivoCSV(archivo);
    
    // Procesar la consulta SQL
    if (soloSelect(consulta)) {
        
        if (posSelect != string::npos) {
            string columnasStr = consulta.substr(posSelect + 7, posFrom - (posSelect + 7)); // 7 es la longitud de "SELECT "
            // Procesar si es SELECT *
            if (columnasStr == "*") {
                extraerColumnas("*");
                imprimirJson();
            }
            // Procesar si es SELECT columna, columna
            else {
                seleccionarTodas = false;
                extraerColumnas(columnasStr);
                for (int i = 0; i < numColumnas; ++i) {
                    string* columna = lista.getColumna(columnas[i], &existeColumna);
                    if (!existeColumna) {
                       continue;
                    }
                    imprimirJsonColumnas(columna, columnas[i]);
                }
            }
        }
    }

    
    //SELECT DISTINCT columna FROM archivo
    if (posDistinct != string::npos) {
        columnasStr = consulta.substr(posSelect + 16, posFrom - (posSelect + 16));    
        extraerColumnas(columnasStr);
        for (int i = 0; i < numColumnas; ++i) {
            string* columna = lista.getColumna(columnas[i], &existeColumna); 
            if (!existeColumna) {
                continue;
            }
            int sizeDistinct = 0;
            cout << "\nColumna: " << columnas[i] << endl;
            string* columnaDistinta = procesarDistinct(columna, sizeDistinct);
            cout << "Número de distintos: " << sizeDistinct << endl;
            imprimirJsonFilas(columnaDistinta, sizeDistinct, columnas[i]);
        }
        return;
    }  
    //SELECT columna FROM archivo WHERE columna (=.>.<) parametro
    else if (posWhere != string::npos) {

    // Encontrar la posición del operador en la consulta    
    size_t posIgual = consulta.find("=");
    size_t posMayor = consulta.find(">");
    size_t posMenor = consulta.find("<");


    size_t posOperador = string::npos;
    int operador = 0;

    // Encontrar el operador en la consulta
    if (posIgual != string::npos) {
        posOperador = posIgual;
        operador = 1;
    } else if (posMayor != string::npos) {
        posOperador = posMayor;
        operador = 2;
    } else if (posMenor != string::npos) {
        posOperador = posMenor;
        operador = 3;
    }

    // Extraer la columna y el parámetro de la consulta
    string columna = consulta.substr(posWhere + 6, posOperador - (posWhere + 6));
    string parametro = consulta.substr(posOperador + 1);

    // Intentar convertir el parámetro a un entero
    int parametroInt = 0;
    bool esNumero = true;

    // Verificar si el parámetro es un número
    try {
        parametroInt = stoi(parametro);
    } catch (const std::invalid_argument&) {
        esNumero = false;  // No es un número
    }

    // Imprimir la información de la consulta
    cout << "Columna: " << columna << endl;
    cout << "Operador: " << operador << endl;
    cout << "Parametro: " << (esNumero ? to_string(parametroInt) : parametro) << "\n" << endl;

    // Obtener los datos de la columna
    string* columnaData = lista.getColumna(columna, &existeColumna);

    // Verificar si la columna existe
    if (existeColumna) {

        // Cambiar el inicio del bucle a 1 para ignorar la primera fila
        for (int i = 0; i < lista.numFilas; ++i) { 
            bool condicionCumplida = false;
            string valorColumna = columnaData[i];  

            // Intentar convertir el valor de la columna a entero
            int valorColumnaInt = 0;
            bool esValorNumero = true;

            // Verificar si el valor de la columna es un número
            try {
                valorColumnaInt = stoi(valorColumna);
            } catch (const std::invalid_argument&) {
                esValorNumero = false; // No es un número
            }

            // Comparar según el operador encontrado
            if (operador == 1) { // Comparación de igual 
                if ((esNumero && esValorNumero && valorColumnaInt == parametroInt) || 
                    (!esNumero && valorColumna == parametro)) {
                    condicionCumplida = true;
                }
            } else if (operador == 2) { // Comparación mayor
                if (esNumero && esValorNumero && valorColumnaInt > parametroInt) {
                    condicionCumplida = true;
                } else if (!esNumero && valorColumna > parametro) {
                    condicionCumplida = true;
                }
            } else if (operador == 3) { // Comparación menor
                if (esNumero && esValorNumero && valorColumnaInt < parametroInt) {
                    condicionCumplida = true;
                } else if (!esNumero && valorColumna < parametro) {
                    condicionCumplida = true;
                }
            }

            if (condicionCumplida) {
                string* fila = lista.getFila(i+1);
                imprimirJsonFilas(fila);  // Imprimir la fila en formato JSON
            }
            }
        }
    }
    //SELECT columna FROM archivo ORDER BY columna
    else if (posOrderBy != string::npos) {
        size_t posOrderBy = consulta.find("ORDER BY");
        string columna = consulta.substr(posOrderBy + 9, posFrom - (posOrderBy + 9));
        cout << "Columna: " << columna << endl;
        string* columnaData = lista.getColumna(columna, &existeColumna);  // Obtener los datos de la columna
        if (existeColumna) {
            procesarOrderBy(columna);
            imprimirJson();
        }
    }
    //SELECT MIN(columna) FROM archivo
    else if (posMin != string::npos) {
         columnasStr = consulta.substr(posSelect + 11, posFrom - (posSelect + 11));
         cout<<"Columnas: "<<columnasStr<<"\n"<<endl;    
         extraerColumnas(columnasStr);
         for (int i = 0; i < numColumnas; ++i) {
            string* columna = lista.getColumna(columnas[i], &existeColumna); 
            if (!existeColumna) {
                continue;
            }
            double minimo = getMin(columna);
            if (minimo == -999) {
                cout << "La columna *" << columnas[i] << "* no es numérica" << endl;
            } else {
                cout << "El valor mínimo de la columna " << columnas[i] << " es: " << minimo << endl;
            }
         }
    //SELECT MAX(columna) FROM archivo
    } else if (posMax != string::npos) {
        columnasStr = consulta.substr(posSelect + 11, posFrom - (posSelect + 11));    
        cout<<"Columnas: "<<columnasStr<<"\n"<<endl;   
        extraerColumnas(columnasStr);
        for (int i = 0; i < numColumnas; ++i) {
            string* columna = lista.getColumna(columnas[i], &existeColumna); 
            if (!existeColumna) {
                continue;
            }
            double maximo = getMax(columna);
            if (maximo == -999) {
                cout << "La columna *" << columnas[i] << "* no es numerica" << endl;
            } else {
                cout << "El valor máximo de la columna " << columnas[i] << " es: " << maximo << endl;
            }
        }
    //SELECT COUNT(columna) FROM archivo
    } else if (posCount != string::npos) {
        columnasStr = consulta.substr(posSelect + 13, posFrom - (posSelect + 13));   
        cout<<"Columnas: "<<columnasStr<<"\n"<<endl;
        extraerColumnas(columnasStr);
        for (int i = 0; i < numColumnas; ++i) {
            string* columna = lista.getColumna(columnas[i], &existeColumna); 
            if (!existeColumna) {
                continue;
            }
            cout << "El número de registros de la columna " << columnas[i] << " es: " << lista.numFilas << endl;
        } 
    //SELECT SUM(columna) FROM archivo
    } else if (posSum != string::npos) {
        columnasStr = consulta.substr(posSelect + 11, posFrom - (posSelect + 11));  
        cout<<"Columnas: "<<columnasStr<<"\n"<<endl;    
        extraerColumnas(columnasStr);
        for (int i = 0; i < numColumnas; ++i) {
            string* columna = lista.getColumna(columnas[i], &existeColumna); 
            if (!existeColumna) {
                continue;
            }
            double suma = 0.0;
            suma = getSum(columna);
            if (suma == -999) {
                cout << "La columna *" << columnas[i] << "* no es numerica" << endl;
            } else {
                cout << "La suma de la columna " << columnas[i] << " es: " << suma << endl;
            }
        }
    //SELECT SUM(columna) FROM archivo
    } else if (posSum != string::npos) {
        columnasStr = consulta.substr(posSelect + 11, posFrom - (posSelect + 11)); 
        cout<<"Columnas: "<<columnasStr<<"\n"<<endl;     
        extraerColumnas(columnasStr);
        for (int i = 0; i < numColumnas; ++i) {
            string* columna = lista.getColumna(columnas[i], &existeColumna); 
            if (!existeColumna) {
                continue;
            }
            double suma = 0.0;
            suma = getSum(columna);
            if (suma == -999) {
                cout << "La columna *" << columnas[i] << "* no es numerica" << endl;
            } else {
                cout << "La suma de la columna " << columnas[i] << " es: " << suma << endl;
            }
        }
    //SELECT AVG(columna) FROM archivo
    } else if (posAvg != string::npos) {
        columnasStr  = consulta.substr(posSelect + 11, posFrom - (posSelect + 11));  
        cout<<"Columnas: "<<columnasStr<<"\n"<<endl;   
        extraerColumnas(columnasStr);
        for (int i = 0; i < numColumnas; ++i) {
            string* columna = lista.getColumna(columnas[i], &existeColumna); 
            if (!existeColumna) {
                continue;
            }
            double suma = 0.0;
            suma = getSum(columna);
            if (suma == -999) {
                cout << "La columna *" << columnas[i] << "* no es numerica" << endl;
            } else {
                cout << "El promedio de la columna " << columnas[i] << " es: " << suma / lista.numFilas << endl;
            }
        }
    }


}

// Método para procesar la consulta DISTINCT
string* ConsultaSQL::procesarDistinct(const string* columna, int& sizeDistinct) const {
    // Crear un array dinámico para almacenar los valores distintos
    string* distintos = new string[lista.numFilas]; 
    int count = 0;  // Contador para los elementos distintos encontrados

    for (int i = 0; i < lista.numFilas; ++i) {
        bool repetido = false;

        // Comparar con los elementos que ya se han añadido al array de distintos
        for (int j = 0; j < count; ++j) {
            if (columna[i] == distintos[j]) {
                repetido = true;
                break;
            }
        }

        // Si no es repetido, lo añadimos al array y aumentamos el contador
        if (!repetido) {
            distintos[count] = columna[i];
            count++;
        }
        
    }
    
    sizeDistinct = count;  // Actualizar el valor de sizeDistinct
    return distintos;  // Retornar el array de valores distintos
}



// Método para imprimir la consulta SQL
bool ConsultaSQL::consulta() {
    cout << "Archivo: " << archivo << endl;
    if (seleccionarTodas) {
        cout << "Columnas: Todas (*)" << endl;
    } else {
        cout << "Columnas seleccionadas: ";
        for (int i = 0; i < numColumnas; ++i) {
            cout << columnas[i] << " ";
        }
        cout << "\n" << endl;
    }
    return true;
}

// Método para recorrer la lista de registros y mostrar el mínimo
double ConsultaSQL::getMin(const string* columnasStr) {
    double minimo = 0.0;
    int contador = 0;
    try {
        minimo = stod(columnasStr[0]);
        double valorActual = 0.0;

        for (int i=0; i< lista.numFilas; ++i) {
            valorActual = stod(columnasStr[i]);
            if (valorActual < minimo) {
                minimo = valorActual;
            }
            contador++;
        }
    } catch(...) {
        // cout << columnasStr[contador]<< " no es numero" << endl;
        return -999;}
    return minimo;
}

// Método para extraer las columnas de la consulta SQL en un SELECT
void ConsultaSQL::extraerColumnas(const string columnasStr) {
    
    // Extraer las columnas entre SELECT y FROM
    if (columnasStr == "*") {
        seleccionarTodas = true;
        numColumnas = lista.cabeza->numColumnas;
        for (int i = 0; i < numColumnas; ++i) {
            columnas[i] = lista.cabeza->valores[i];
        }

    } else {
        seleccionarTodas = false;
        size_t start = 0;
        size_t end = 0;
        numColumnas = 0;

        // Extraer las columnas individuales
        while ((end = columnasStr.find(",", start)) != string::npos) {
            columnas[numColumnas++] = columnasStr.substr(start, end - start);
            start = end + 1;  // Avanzar al siguiente carácter después de la coma
        }
        columnas[numColumnas++] = columnasStr.substr(start); // Para la última columna
        this->numColumnas = numColumnas;
    }
    
}

// Método para recorrer la lista de registros y mostrar el máximo
double ConsultaSQL::getMax(const string* columnasStr) {
    double maximo = 0.0;
    int contador = 0;
    try {
        maximo = stod(columnasStr[0]);
        double valorActual = 0.0;

        for (int i=0; i< lista.numFilas; ++i) {
            valorActual = stod(columnasStr[i]); //Stod: string to double
            if (valorActual > maximo) {
                maximo = valorActual;
            }
            contador++;
        }
    } catch(...) {
        return -999;} //Si no es un numero
    return maximo;
}

// Método para recorrer la lista de registros y mostrar la suma
double ConsultaSQL::getSum(const string* columnasStr) {
    double suma = 0.0;
    int contador = 0;
    try {
        double valorActual = 0.0;

        for (int i=0; i< lista.numFilas; ++i) {
            valorActual = stod(columnasStr[i]);
            suma += valorActual;
            contador++;
        }
    } catch(...) {
        return -999;} //Si no es un numero
    return suma;
}

bool ConsultaSQL::soloSelect(const string& consulta) {
    size_t posSelect = consulta.find("SELECT");
    size_t posFrom = consulta.find(" FROM ");
    size_t posDistinct = consulta.find("SELECT DISTINCT");
    size_t posMin = consulta.find("SELECT MIN");
    size_t posMax = consulta.find("SELECT MAX");
    size_t posCount = consulta.find("SELECT COUNT");
    size_t posSum = consulta.find("SELECT SUM");
    size_t posAvg = consulta.find("SELECT AVG");
    size_t posWhere = consulta.find("WHERE");
    size_t posOrderBy = consulta.find("ORDER BY");

    if (posSelect != string::npos && posFrom != string::npos && posDistinct == string::npos 
    && posMin == string::npos && posMax == string::npos && posCount == string::npos && 
    posSum == string::npos && posAvg == string::npos && posWhere == string::npos && posOrderBy == string::npos) {
        return true;
    }
    return false;
}
void ConsultaSQL::imprimirJsonFilas(string* fila) const {
    // Apertura del objeto JSON
    cout << "{" << endl;
    
    // Recorrer las columnas
    for (int i = 0; i < lista.cabeza->numColumnas; ++i) {
        // Imprimir el nombre de la columna y su valor correspondiente en formato JSON
        cout << "  \"" << lista.cabeza->valores[i] << "\": \"" << fila[i] << "\"";
        
        // Colocar una coma después de cada par clave-valor excepto el último
        if (i < lista.cabeza->numColumnas - 1) {
            cout << ",";
        }
        cout << endl;
    }
    
    // Cierre del objeto JSON
    cout << "}";
}
void ConsultaSQL::imprimirJsonFilas(string* fila, int numDistintos, string nombre) const {
    // Apertura del objeto JSON
    cout << "{" << endl;
    
    // Imprimir el nombre del campo antes de recorrer las filas
    cout << "  \"" << nombre << "\": [" << endl;

    // Recorrer las filas usando el parámetro numDistintos
    for (int i = 0; i < numDistintos; ++i) {
        // Imprimir el valor correspondiente en formato JSON
        cout << "    \"" << fila[i] << "\"";
        
        // Colocar una coma después de cada valor excepto el último
        if (i < numDistintos - 1) {
            cout << ",";
        }
        cout << endl;
    }
    
    // Cierre del objeto JSON
    cout << "  ]" << endl;
    cout << "}" << endl;
}



void ConsultaSQL::imprimirJsonColumnas(string* columna, string nombre) const {
    // Apertura del objeto JSON
    cout << "{" << endl;

    // Imprimir el nombre de la columna seguido de su contenido en formato JSON
    cout << "  \"" << nombre << "\": [" << endl;

    // Recorrer las filas (valores de la columna)
    for (int i = 0; i < lista.numFilas; ++i) {
        // Imprimir el valor de la columna
        cout << "    \"" << columna[i] << "\"";

        // Colocar una coma después de cada valor excepto el último
        if (i < lista.numFilas - 1) {
            cout << ",";
        }
        cout << endl;
    }

    // Cierre del arreglo y el objeto JSON
    cout << "  ]" << endl;
    cout << "}";
}

void ConsultaSQL::imprimirJson() const {
    Registro *actual = lista.cabeza;

    // saltar la primera fila (nombre de las columnas)
    actual = actual->siguiente;
    
    // Comienzo del arreglo JSON
    cout << "[" << endl;

    // Iterar sobre las filas (registros)
    for (int i = 0; actual != nullptr; ++i) {
        cout << "  {" << endl;

        // Iterar sobre las columnas (valores de la fila actual)
        for (int j = 0; j < actual->numColumnas; ++j) {
            cout << "    \"" << lista.cabeza->valores[j] << "\": \"" << actual->valores[j] << "\"";
            
            // Añadir una coma después de cada par clave-valor excepto el último
            if (j < actual->numColumnas - 1) {
                cout << ",";
            }
            cout << endl;
        }

        // Cerrar el objeto de la fila
        cout << "  }";

        // Añadir una coma después de cada objeto excepto el último
        if (actual->siguiente != nullptr) {
            cout << ",";
        }
        cout << endl;

        // Avanzar al siguiente registro (fila)
        actual = actual->siguiente;
    }

    // Cierre del arreglo JSON
    cout << "]" << endl;
}
void ConsultaSQL::procesarOrderBy(string columna) const {
    if (lista.cabeza == nullptr || lista.cabeza->siguiente == nullptr) {
        cout  << "lista nula" << endl;
        return;  // Lista vacía o de un solo nodo, no hay nada que ordenar
    }
    
    // Encontrar el índice de la columna en la cabeza
    int indice = -1;
    for (int i = 0; lista.cabeza->valores[i] != ""; i++) {
        if (lista.cabeza->valores[i] == columna) {
            indice = i;
            break;
        }
    }

    // Si no se encontró la columna, mostrar un mensaje y salir
    if (indice == -1) {
        cout << "Columna no encontrada" << endl;
        return;
    }

    // Ahora podemos ordenar la lista enlazada según el valor en el índice encontrado
    bool huboIntercambio;
    do {
        huboIntercambio = false;
        Registro* actual = lista.cabeza->siguiente->siguiente;
        Registro* anterior = lista.cabeza->siguiente;
        
        while (actual != nullptr) {
            // Comparar valores en el índice específico
            if (anterior->valores[indice] > actual->valores[indice]) {
                // Intercambiar los valores completos de ambos nodos
                // template
                //std vector<   >
                swap(anterior->valores, actual->valores);
                huboIntercambio = true;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
    } while (huboIntercambio);
}