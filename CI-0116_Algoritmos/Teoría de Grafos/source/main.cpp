/**
 * @file main.cpp
 * @brief Programa principal del Sistema Nacional de Tipificación de Emergencias Potenciales
 * @author Camila Rodríguez Águila - C36624
 * @date 2025
 */

#include "Grafo.h"
#include "FileReader.h"
#include "AnalizadorGrafo.h"
#include "InterfazUsuario.h"
#include <iostream>
#include <string>

/**
 * @brief Función principal
 * @param argc Número de argumentos
 * @param argv Array de argumentos
 * @return Código de salida
 */
int main(int argc, char* argv[]) {
    std::string archivo;
    
    // Verificar argumentos de línea de comandos
    if (argc > 1) {
        archivo = argv[1];
    } else {
        std::cout << "Ingrese el nombre del archivo CSV: ";
        std::getline(std::cin, archivo);
    }
    
    // Crear instancias de las clases
    Grafo grafo;
    FileReader reader;
    
    // Leer el archivo CSV
    std::cout << "\nCargando datos desde: " << archivo << std::endl;
    
    if (!reader.leerCSV(archivo, grafo)) {
        std::cerr << "Error: No se pudo cargar el archivo " << archivo << std::endl;
        std::cerr << "Uso: " << argv[0] << " <archivo.csv>" << std::endl;
        return 1;
    }
    
    std::cout << "Datos cargados exitosamente." << std::endl;
    std::cout << "Ciudades en el sistema: " << grafo.getNumVertices() << std::endl;
    
    // Crear analizador y procesar el grafo
    std::cout << "Procesando grafo y calculando rutas óptimas..." << std::endl;
    AnalizadorGrafo analyzer(&grafo);
    analyzer.analizarGrafo();
    std::cout << "Análisis completado. \n" << std::endl;
    
    // Crear interfaz de usuario y ejecutar menú principal
    InterfazUsuario ui(&grafo, &analyzer);
    ui.run();
    
    return 0;
}