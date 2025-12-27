// Clase para leer un archivo CSV y crear una lista enlazada de registros(Nodos) con los datos del archivo
#include "../include/ListaRegistros.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Método principal para leer un archivo CSV y crear una lista de registros
void ListaRegistros::leerArchivoCSV(const string &rutaArchivo)
{
    // Verificar si el archivo se puede abrir
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    // Variables para procesar el archivo
    string linea;
    bool esPrimeraLinea = true;
    int numColumnas = 0;
    Registro *actual = nullptr;
    numFilas = 0; // Inicializar el contador de filas

    // Leer el archivo línea por línea
    while (getline(archivo, linea))
    {
        // Crear un stream para procesar la línea
        stringstream ss(linea);
        string valor;

        // Si es la primera línea, contamos las columnas (encabezados)
        if (esPrimeraLinea)
        {
            // Contar el número de columnas
            while (getline(ss, valor, ','))
            {
                numColumnas++;
            }
            esPrimeraLinea = false;

            // Resetear el stream para procesar la primera línea de nuevo
            ss.clear();
            ss.str(linea);
        }

        // Crear un nuevo objeto Registro(Nodo) con el número de columnas
        Registro *nuevoRegistro = new Registro(numColumnas);

        // Asignar los valores de la línea actual al nuevo registro
        for (int i = 0; i < numColumnas; ++i)
        {
            getline(ss, nuevoRegistro->valores[i], ',');
        }

        // Conectar el nuevo registro a la lista
        if (cabeza == nullptr)
        {
            cabeza = nuevoRegistro; // Primer registro en la lista
        }
        else
        {
            // Enlazar el nuevo registro al final de la lista
            actual->siguiente = nuevoRegistro; // Conectar al siguiente nodo
            numFilas++;
        }
        actual = nuevoRegistro; // Actualizar el puntero actual
    }
    // Actualizar el número de filas y cerrar el archivo
    this->numFilas = numFilas;
    archivo.close();
}

// Método para imprimir toda la lista de registros
void ListaRegistros::imprimirLista(int numcolumnas, string *columnas, bool imprimirTodas) const //const para que no se pueda cambiar la lista
{
    // Imprimir todas las columnas si imprimirTodas es verdadero, en la consulta usó *
    if (imprimirTodas)
    {
        Registro *actual = cabeza;
        while (actual != nullptr)
        {
            actual->imprimir();
            actual = actual->siguiente;
        }
    }
    else
    {
        // Imprimir las columnas seleccionadas
        for (int i = 0; i < numcolumnas; ++i)
        {
            // Imprimir el nombre de la columna
            cout << columnas[i] << "\n" << endl;
            Registro *actual = cabeza; // Puntero al primer registro

            // Encontrar la columna seleccionada en la primera linea (nombre de las columnas)

            int contador = 0;//Contador para saber que columna imprimir

            for (int j = 0; j < numcolumnas; ++j)
            {
                //Si el valor de la columna no es igual a la columna seleccionada se aumenta el contador
                if (actual->valores[j] != columnas[i])
                {contador++;}
                else
                {break;}
            }

            // Saltarse la primera linea
            actual = actual->siguiente;

            // Imprimir los registros uno por uno usando el contador para saber que columna imprimir
            while (actual != nullptr)
            {
                actual->imprimir(contador);
                actual = actual->siguiente;
            }
            cout << endl;
        }
    }
}

// Método para obtener una columna específica de la lista de registros
string* ListaRegistros::getColumna(string nombreColumna, bool* booleano) const {

    // Inicializar el puntero booleano para verificar si se encontró la columna
    *booleano = true;

    // Encontrar la columna seleccionada en la primera fila (nombre de las columnas)
    Registro *actual = cabeza; // Puntero al primer registro para buscar la columna
    int numColumna = -1;  // Inicializa en -1 para detectar si no se encuentra la columna, contador de columnas

    // Buscar la columna en la primera fila por el nombre de la columna
    for (int j = 0; j < actual->numColumnas; ++j) {
        // Si el valor de la columna es el que se busca, almacenamos el índice y sale del ciclo
        if (actual->valores[j] == nombreColumna) {
            numColumna = j;
            break;
        }
    }

    // Verifica si se encontró la columna para evitar errores
    if (numColumna == -1) {
        *booleano = false;
        cerr << "Error: No se encontró la columna *" << nombreColumna << "*"<< endl;
        return nullptr;
    }

    // Saltarse la primera fila (nombres de columnas) para obtener los valores de los registros
    actual = actual->siguiente;

    // Crear un arreglo dinámico para almacenar los valores de la columna
    string *columnaArray = new string[numFilas];
    int index = 0; // Índice para almacenar los valores en el arreglo

    // Almacenar los valores de la columna en el arreglo para devolver los valores de la columna
    while (actual != nullptr) {
        columnaArray[index++] = actual->valores[numColumna];
        actual = actual->siguiente;
    }

    return columnaArray;
}
//Metodo para obtener la fila que contiene un valor específico
string* ListaRegistros::getFila(int fila) const {
    Registro *actual = cabeza;
    int contador = 0;
    while (actual != nullptr) {
        if (contador == fila) {
            return actual->valores;
        }
        actual = actual->siguiente;
        contador++;
    }
    return nullptr;
}

//Metodo para obtener la fila que contiene un valor específico
string* ListaRegistros::getFila(string valor) const { 
    Registro *actual = cabeza;
    // Recorrer la lista de registros para encontrar el valor en la fila
    while (actual != nullptr) {
        // Buscar el valor en los valores de la fila
        for (int i = 0; i < actual->numColumnas; ++i) {
            if (actual->valores[i] == valor) {
                // retorna la primera fila que contiene el valor
                return actual->valores;
            }
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

