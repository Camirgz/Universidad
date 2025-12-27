#include "AnalizadorGrafo.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <climits>

AnalizadorGrafo::AnalizadorGrafo(Grafo* g) : grafo(g), esAnalizado(false) {}

AnalizadorGrafo::~AnalizadorGrafo() {}

void AnalizadorGrafo::analizarGrafo() {
    if (grafo) {
        grafo->floydWarshall(distancias, sgteVertice);
        esAnalizado = true;
    }
}

QueryResult AnalizadorGrafo::distribucionOptima() {
    QueryResult resultado;
    
    if (!esAnalizado) {
        analizarGrafo();
    }
    
    int n = grafo->getNumVertices();
    long long minTotalTime = LLONG_MAX;
    
    for (int i = 0; i < n; i++) {
        long long totalTime = calculateTotalTimeFromCity(i);
        
        if (totalTime < minTotalTime) {
            minTotalTime = totalTime;
            resultado.ciudades.clear();
            resultado.ciudades.push_back(grafo->getNombreVertice(i));
        } else if (totalTime == minTotalTime) {
            resultado.ciudades.push_back(grafo->getNombreVertice(i));
        }
    }
    
    resultado.distance = static_cast<int>(minTotalTime);
    return resultado;
}

QueryResult AnalizadorGrafo::mejorDispatcher(const std::string& targetCity) {
    QueryResult resultado;
    
    if (!esAnalizado) {
        analizarGrafo();
    }
    
    int targetId = grafo->getIdVertice(targetCity);
    if (targetId == -1) {
        return resultado; // Ciudad no encontrada
    }
    
    int n = grafo->getNumVertices();
    int distanciaMin = INF;
    int mejorId = -1;
    
    for (int i = 0; i < n; i++) {
        if (i != targetId && distancias[i][targetId] < distanciaMin) {
            distanciaMin = distancias[i][targetId];
            mejorId = i;
        }
    }
    
    if (mejorId != -1 && distanciaMin != INF) {
        resultado.ciudades.push_back(grafo->getNombreVertice(mejorId));
        resultado.distance = distanciaMin;
        
        // Reconstruir el camino
        std::vector<int> pathIds = grafo->reconstruirCamino(sgteVertice, mejorId, targetId);
        resultado.path = grafo->caminoNombre(pathIds);
        
        // Verificar si hay múltiples ciudades con la misma distancia mínima
        for (int i = 0; i < n; i++) {
            if (i != targetId && i != mejorId && distancias[i][targetId] == distanciaMin) {
                resultado.ciudades.push_back(grafo->getNombreVertice(i));
            }
        }
    }
    
    return resultado;
}

QueryResult AnalizadorGrafo::ciudadesDistantes() {
    QueryResult resultado;
    
    if (!esAnalizado) {
        analizarGrafo();
    }
    
    int n = grafo->getNumVertices();
    int distanciaMax = 0;
    int mejor = -1, mejorTarget = -1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && distancias[i][j] != INF && distancias[i][j] > distanciaMax) {
                distanciaMax = distancias[i][j];
                mejor = i;
                mejorTarget = j;
            }
        }
    }
    
    if (mejor != -1 && mejorTarget != -1) {
        resultado.ciudades.push_back(grafo->getNombreVertice(mejor));
        resultado.ciudades.push_back(grafo->getNombreVertice(mejorTarget));
        resultado.distance = distanciaMax;
        
        // Reconstruir el camino
        std::vector<int> pathIds = grafo->reconstruirCamino(sgteVertice, mejor, mejorTarget);
        resultado.path = grafo->caminoNombre(pathIds);
        
        // Buscar otros pares con la misma distancia máxima
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && distancias[i][j] == distanciaMax && 
                    (i != mejor || j != mejorTarget)) {
                    // Evitar duplicados
                    bool isDuplicate = false;
                    for (size_t k = 0; k < resultado.ciudades.size(); k += 2) {
                        if ((resultado.ciudades[k] == grafo->getNombreVertice(i) && 
                             resultado.ciudades[k+1] == grafo->getNombreVertice(j))) {
                            isDuplicate = true;
                            break;
                        }
                    }
                    if (!isDuplicate) {
                        resultado.ciudades.push_back(grafo->getNombreVertice(i));
                        resultado.ciudades.push_back(grafo->getNombreVertice(j));
                    }
                }
            }
        }
    }
    
    return resultado;
}

QueryResult AnalizadorGrafo::findLeastDistantCities() {
    QueryResult resultado;
    
    if (!esAnalizado) {
        analizarGrafo();
    }
    
    int n = grafo->getNumVertices();
    int distanciaMin = INF;
    int mejor = -1, mejorTarget = -1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && distancias[i][j] != INF && distancias[i][j] < distanciaMin) {
                distanciaMin = distancias[i][j];
                mejor = i;
                mejorTarget = j;
            }
        }
    }
    
    if (mejor != -1 && mejorTarget != -1) {
        resultado.ciudades.push_back(grafo->getNombreVertice(mejor));
        resultado.ciudades.push_back(grafo->getNombreVertice(mejorTarget));
        resultado.distance = distanciaMin;
        
        // Reconstruir el camino
        std::vector<int> pathIds = grafo->reconstruirCamino(sgteVertice, mejor, mejorTarget);
        resultado.path = grafo->caminoNombre(pathIds);
        
        // Buscar otros pares con la misma distancia mínima
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && distancias[i][j] == distanciaMin && 
                    (i != mejor || j != mejorTarget)) {
                    resultado.ciudades.push_back(grafo->getNombreVertice(i));
                    resultado.ciudades.push_back(grafo->getNombreVertice(j));
                }
            }
        }
    }
    
    return resultado;
}

std::vector<std::pair<std::string, double>> AnalizadorGrafo::getCitiesRankedByAvgTime() {
    std::vector<std::pair<std::string, double>> ranking;
    
    if (!esAnalizado) {
        analizarGrafo();
    }
    
    int n = grafo->getNumVertices();
    
    for (int i = 0; i < n; i++) {
        double tiempoAvg = calculateAvgTimeFromCity(i);
        ranking.emplace_back(grafo->getNombreVertice(i), tiempoAvg); 
    }
    
    // Ordenar por tiempo promedio
    std::sort(ranking.begin(), ranking.end(), 
          [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) { 
              return a.second < b.second; 
          });

    return ranking;
}

long long AnalizadorGrafo::calculateTotalTimeFromCity(int cityId) {
    long long totalTime = 0;
    int n = grafo->getNumVertices();
    
    for (int j = 0; j < n; j++) {
        if (cityId != j && distancias[cityId][j] != INF) {
            totalTime += distancias[cityId][j];
        }
    }
    
    return totalTime;
}

double AnalizadorGrafo::calculateAvgTimeFromCity(int cityId) {
    long long totalTime = calculateTotalTimeFromCity(cityId);
    int n = grafo->getNumVertices();
    
    return static_cast<double>(totalTime) / (n - 1);
}
