#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <unordered_map>
#include <limits>

/**
 * @brief Estructura que representa una arista del grafo
 */
struct arista {
    int target;
    int peso;
    
    arista(int t, int w) : target(t), peso(w) {}
};

/**
 * @brief Estructura que representa un vértice del grafo
 */
struct Vertex {
    int id;
    std::string nombre;
    std::vector<arista> adyacentes;
    
    Vertex() : id(-1), nombre("") {}
    Vertex(int i, const std::string& n) : id(i), nombre(n) {}
};

/**
 * @brief Clase que representa un grafo dirigido ponderado
 */
class Grafo {
private:
    std::vector<Vertex> vertices;
    std::unordered_map<std::string, int> nameToId; // Mapa para buscar ID por nombre
    int numVertices;
    
    static const int INF = std::numeric_limits<int>::max();

public:
    /**
     * @brief Constructor por defecto
     */
    Grafo();
    
    /**
     * @brief Destructor
     */
    ~Grafo();
    
    /**
     * @brief Agrega un vértice al grafo
     * @param nombre Nombre de la ciudad
     * @return ID del vértice agregado
     */
    int añadirVertice(const std::string& nombre);
    
    /**
     * @brief Agrega una arista al grafo
     * @param sourceId ID del vértice origen
     * @param targetId ID del vértice destino
     * @param peso Peso de la arista
     */
    void añadirArista(int sourceId, int targetId, int peso);
    
    /**
     * @brief Obtiene el ID de un vértice por su nombre
     * @param nombre Nombre de la ciudad
     * @return ID del vértice, -1 si no existe
     */
    int getIdVertice(const std::string& nombre) const;
    
    /**
     * @brief Obtiene el nombre de un vértice por su ID
     * @param id ID del vértice
     * @return Nombre de la ciudad
     */
    std::string getNombreVertice(int id) const;
    
    /**
     * @brief Obtiene el número de vértices del grafo
     * @return Número de vértices
     */
    int getNumVertices() const;
    
    /**
     * @brief Algoritmo de Floyd-Warshall para encontrar todos los caminos más cortos
     * @param dist Matriz de distancias (salida)
     * @param next Matriz de siguiente vértice en el camino (salida)
     */
    void floydWarshall(std::vector<std::vector<int>>& dist, 
                       std::vector<std::vector<int>>& next) const;
    
    /**
     * @brief Reconstruye el camino entre dos vértices
     * @param next Matriz de siguiente vértice
     * @param start Vértice de inicio
     * @param end Vértice de fin
     * @return Vector con el camino
     */
    std::vector<int> reconstruirCamino(const std::vector<std::vector<int>>& next, 
                                   int start, int end) const;
    
    /**
     * @brief Convierte un camino de IDs a nombres
     * @param path Vector de IDs
     * @return Vector de nombres
     */
    std::vector<std::string> caminoNombre(const std::vector<int>& path) const;
    
    /**
     * @brief Imprime el grafo para debugging
     */
    void printGrafo() const;
};

#endif // GRAPH_H