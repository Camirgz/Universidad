#ifndef GRAPHANALYZER_H
#define GRAPHANALYZER_H

#include "Grafo.h"
#include <vector>
#include <string>
#include <utility>

/**
 * @brief Estructura para almacenar información de consultas
 */
struct QueryResult {
    std::vector<std::string> ciudades;
    std::vector<std::string> path;
    int distance;
    
    QueryResult() : distance(0) {}
};

/**
 * @brief Clase para realizar análisis sobre grafos
 */
class AnalizadorGrafo {
private:
    Grafo* grafo;
    std::vector<std::vector<int>> distancias;
    std::vector<std::vector<int>> sgteVertice;
    bool esAnalizado;
    
    static const int INF = std::numeric_limits<int>::max();

public:
    /**
     * @brief Constructor
     * @param g Puntero al grafo a analizar
     */
    AnalizadorGrafo(Grafo* g);
    
    /**
     * @brief Destructor
     */
    ~AnalizadorGrafo();
    
    /**
     * @brief Realiza el análisis del grafo (ejecuta Floyd-Warshall)
     */
    void analizarGrafo();
    
    /**
     * @brief Pregunta 1: Ciudad más efectiva para distribución
     * @return Resultado con las ciudades óptimas
     */
    QueryResult distribucionOptima();
    
    /**
     * @brief Pregunta 2: Mejor ciudad para despachar hacia una ciudad específica
     * @param targetCity Nombre de la ciudad objetivo
     * @return Resultado con la mejor ciudad origen
     */
    QueryResult mejorDispatcher(const std::string& targetCity);
    
    /**
     * @brief Pregunta 3: Par de ciudades más distantes
     * @return Resultado con el par más distante
     */
    QueryResult ciudadesDistantes();
    
    /**
     * @brief Pregunta 4: Par de ciudades menos distantes (diferentes)
     * @return Resultado con el par menos distante
     */
    QueryResult findLeastDistantCities();
    
    /**
     * @brief Pregunta 5: Lista de ciudades ordenadas por tiempo promedio
     * @return Vector de pares (ciudad, tiempo promedio)
     */
    std::vector<std::pair<std::string, double>> getCitiesRankedByAvgTime();
    
private:
    /**
     * @brief Calcula el tiempo total desde una ciudad hacia todas las demás
     * @param cityId ID de la ciudad
     * @return Tiempo total
     */
    long long calculateTotalTimeFromCity(int cityId);
    
    /**
     * @brief Calcula el tiempo promedio desde una ciudad hacia todas las demás
     * @param cityId ID de la ciudad
     * @return Tiempo promedio
     */
    double calculateAvgTimeFromCity(int cityId);
};

#endif // GRAPHANALYZER_H