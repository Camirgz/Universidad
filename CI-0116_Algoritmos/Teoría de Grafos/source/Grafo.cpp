#include "Grafo.h"
#include <iostream>
#include <algorithm>

Grafo::Grafo() : numVertices(0) {}

Grafo::~Grafo() {}

int Grafo::añadirVertice(const std::string& nombre) {
    // Verificar si el vértice ya existe
    auto it = nameToId.find(nombre);
    if (it != nameToId.end()) {
        return it->second;
    }
    
    // Crear nuevo vértice
    int id = numVertices++;
    vertices.emplace_back(id, nombre);
    nameToId[nombre] = id;
    
    return id;
}

void Grafo::añadirArista(int sourceId, int targetId, int peso) {
    if (sourceId >= 0 && sourceId < numVertices && 
        targetId >= 0 && targetId < numVertices) {
        vertices[sourceId].adyacentes.emplace_back(targetId, peso);
    }
}

int Grafo::getIdVertice(const std::string& nombre) const {
    auto it = nameToId.find(nombre);
    return (it != nameToId.end()) ? it->second : -1;
}

std::string Grafo::getNombreVertice(int id) const {
    if (id >= 0 && id < numVertices) {
        return vertices[id].nombre;
    }
    return "";
}

int Grafo::getNumVertices() const {
    return numVertices;
}

void Grafo::floydWarshall(std::vector<std::vector<int>>& dist, 
                         std::vector<std::vector<int>>& next) const {
    int n = numVertices;
    
    // Inicializar matrices
    dist.assign(n, std::vector<int>(n, INF));
    next.assign(n, std::vector<int>(n, -1));
    
    // Distancia de un vértice a sí mismo es 0
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }
    
    // Inicializar con las aristas directas
    for (int i = 0; i < n; i++) {
        for (const arista& arista : vertices[i].adyacentes) {
            dist[i][arista.target] = arista.peso;
            next[i][arista.target] = arista.target;
        }
    }
    
    // Algoritmo Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
    }
}

std::vector<int> Grafo::reconstruirCamino(const std::vector<std::vector<int>>& next, 
                                      int start, int end) const {
    std::vector<int> path;
    
    if (next[start][end] == -1) {
        return path; // No hay camino
    }
    
    int current = start;
    while (current != end) {
        path.push_back(current);
        current = next[current][end];
    }
    path.push_back(end);
    
    return path;
}

std::vector<std::string> Grafo::caminoNombre(const std::vector<int>& path) const {
    std::vector<std::string> names;
    for (int id : path) {
        names.push_back(getNombreVertice(id));
    }
    return names;
}

void Grafo::printGrafo() const {
    std::cout << "Grafo con " << numVertices << " vértices:" << std::endl;
    for (const Vertex& v : vertices) {
        std::cout << "Vértice " << v.id << " (" << v.nombre << "): ";
        for (const arista& e : v.adyacentes) {
            std::cout << "-> " << vertices[e.target].nombre << "(" << e.peso << ") ";
        }
        std::cout << std::endl;
    }
}