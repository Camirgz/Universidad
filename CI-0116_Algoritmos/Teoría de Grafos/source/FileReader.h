#ifndef FILEREADER_H
#define FILEREADER_H

#include "Grafo.h"
#include <string>

/**
 * @brief Clase para leer archivos CSV y construir grafos
 */
class FileReader {
public:
    /**
     * @brief Constructor por defecto
     */
    FileReader();
    
    /**
     * @brief Destructor
     */
    ~FileReader();
    
    /**
     * @brief Lee un archivo CSV y construye un grafo
     * @param archivo Nombre del archivo CSV
     * @param grafo Referencia al grafo donde se almacenarán los datos
     * @return true si se leyó correctamente, false en caso contrario
     */
    bool leerCSV(const std::string& archivo, Grafo& grafo);
    
private:
    /**
     * @brief Elimina espacios en blanco al inicio y final de una cadena
     * @param str Cadena a procesar
     * @return Cadena sin espacios
     */
    std::string trim(const std::string& str);
    
    /**
     * @brief Divide una línea CSV en tokens
     * @param linea Línea a dividir
     * @return Vector de tokens
     */
    std::vector<std::string> dividirCSV(const std::string& linea);
};

#endif // FILEREADER_H