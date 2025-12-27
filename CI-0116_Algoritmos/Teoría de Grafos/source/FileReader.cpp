#include "FileReader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

FileReader::FileReader() {}

FileReader::~FileReader() {}

bool FileReader::leerCSV(const std::string& archivo, Grafo& grafo) {
    std::ifstream file(archivo);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << archivo << std::endl;
        return false;
    }
    
    std::string linea;
    bool isFirstLine = true;
    
    while (std::getline(file, linea)) {
        // Saltar la primera línea (encabezados)
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        
        // Dividir la línea en tokens
        std::vector<std::string> tokens = dividirCSV(linea);
        
        if (tokens.size() >= 5) {
            try {
                // Parsear los datos
                std::string sourceName = trim(tokens[1]);
                std::string targetName = trim(tokens[3]);
                int peso = std::stoi(trim(tokens[4]));
                // Agregar vértices al grafo
                int actualSourceId = grafo.añadirVertice(sourceName);
                int actualTargetId = grafo.añadirVertice(targetName);
                
                // Agregar arista
                grafo.añadirArista(actualSourceId, actualTargetId, peso);
                
            } catch (const std::exception& e) {
                std::cerr << "Error al procesar línea: " << linea << std::endl;
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
    
    file.close();
    return true;
}

std::string FileReader::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }
    
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

std::vector<std::string> FileReader::dividirCSV(const std::string& linea) {
    std::vector<std::string> tokens;
    std::stringstream ss(linea);
    std::string token;
    
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    
    return tokens;
}