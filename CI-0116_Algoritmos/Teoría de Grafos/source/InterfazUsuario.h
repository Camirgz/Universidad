#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Grafo.h"
#include "AnalizadorGrafo.h"
#include <string>

/**
 * @brief Clase para manejar la interfaz de usuario
 */
class InterfazUsuario {
private:
    Grafo* grafo;
    AnalizadorGrafo* analyzer;

public:
    /**
     * @brief Constructor
     * @param g Puntero al grafo
     * @param a Puntero al analizador
     */
    InterfazUsuario(Grafo* g, AnalizadorGrafo* a);
    
    /**
     * @brief Destructor
     */
    ~InterfazUsuario();
    
    /**
     * @brief Ejecuta el menú principal de la aplicación
     */
    void run();
    
private:
    /**
     * @brief Muestra el menú principal
     */
    void showMainMenu();
    
    /**
     * @brief Muestra información del grafo cargado
     */
    void showGrafoInfo();
    
    /**
     * @brief Ejecuta la consulta 1: Centro de distribución óptimo
     */
    void centroDistribucion();
    
    /**
     * @brief Ejecuta la consulta 2: Mejor ciudad para despacho
     */
    void ciudadDespacho();
    
    /**
     * @brief Ejecuta la consulta 3: Ciudades más distantes
     */
    void masDistante();
    
    /**
     * @brief Ejecuta la consulta 4: Ciudades menos distantes
     */
    void menosDistante();
    
    /**
     * @brief Ejecuta la consulta 5: Ranking de ciudades por tiempo promedio
     */
    void tiemposPromedio();
    
    /**
     * @brief Imprime un resultado de consulta
     * @param resultado Resultado a imprimir
     * @param queryNumber Número de consulta
     */
    void printResultado(const QueryResult& resultado, int queryNumber);
    
    /**
     * @brief Imprime un camino
     * @param path Vector de nombres de ciudades
     */
    void printPath(const std::vector<std::string>& path);
    
    /**
     * @brief Obtiene entrada del usuario
     * @return Opción seleccionada
     */
    int getUserInput();
    
    /**
     * @brief Obtiene una cadena del usuario
     * @param prompt Mensaje a mostrar
     * @return Cadena ingresada
     */
    std::string getUserString(const std::string& prompt);
    
    /**
     * @brief Pausa y espera que el usuario presione Enter
     */
    void pauseForUser();
};

#endif // USERINTERFACE_H