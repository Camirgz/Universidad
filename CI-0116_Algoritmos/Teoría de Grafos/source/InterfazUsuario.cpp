#include "InterfazUsuario.h"
#include <iostream>
#include <iomanip>
#include <limits>

InterfazUsuario::InterfazUsuario(Grafo* g, AnalizadorGrafo* a) : grafo(g), analyzer(a) {}

InterfazUsuario::~InterfazUsuario() {}

void InterfazUsuario::run() {
    int option;
    
    std::cout << "=== Sistema Nacional de Tipificación de Emergencias Potenciales ===" << std::endl;
    std::cout << "Bienvenido al sistema SiNTiEmPo" << std::endl << std::endl;
    
    do {
        showMainMenu();
        option = getUserInput();
        
        switch (option) {
            case 1:
                centroDistribucion();
                break;
            case 2:
                ciudadDespacho();
                break;
            case 3:
                masDistante();
                break;
            case 4:
                menosDistante();
                break;
            case 5:
                tiemposPromedio();
                break;
            case 6:
                showGrafoInfo();
                break;
            case 0:
                std::cout << "Gracias por usar el sistema SiNTiEmPo" << std::endl;
                break;
            default:
                std::cout << "Opción inválida. Por favor, intente de nuevo." << std::endl;
                pauseForUser();
                break;
        }
        
    } while (option != 0);
}

void InterfazUsuario::showMainMenu() {
    std::cout << "\n==================== MENÚ PRINCIPAL ====================" << std::endl;
    std::cout << "1. Centro de distribución más efectivo" << std::endl;
    std::cout << "2. Mejor ciudad para despacho hacia una ciudad específica" << std::endl;
    std::cout << "3. Par de ciudades más distantes" << std::endl;
    std::cout << "4. Par de ciudades menos distantes" << std::endl;
    std::cout << "5. Ranking de ciudades por tiempo promedio" << std::endl;
    std::cout << "6. Información del grafo cargado" << std::endl;
    std::cout << "0. Salir" << std::endl;
    std::cout << "=========================================================" << std::endl;
    std::cout << "\nSeleccione una opción: ";
}

void InterfazUsuario::showGrafoInfo() {
    std::cout << "\n================= INFORMACIÓN DEL GRAFO =================" << std::endl;
    std::cout << "Número de ciudades: " << grafo->getNumVertices() << std::endl;
    std::cout << "=========================================================" << std::endl;
    pauseForUser();
}

void InterfazUsuario::centroDistribucion() {
    std::cout << "\n============== CENTRO DE DISTRIBUCIÓN ÓPTIMO ==============" << std::endl;
    std::cout << "Calculando el centro más efectivo para distribución..." << std::endl;
    
    QueryResult resultado = analyzer->distribucionOptima();
    printResultado(resultado, 1);
    pauseForUser();
}

void InterfazUsuario::ciudadDespacho() {
    std::cout << "\n============= MEJOR CIUDAD PARA DESPACHO =================" << std::endl;
    
    std::string targetCity = getUserString("Ingrese el nombre de la ciudad objetivo: ");
    
    std::cout << "Calculando la mejor ciudad para despachar hacia " << targetCity << "..." << std::endl;
    
    QueryResult resultado = analyzer->mejorDispatcher(targetCity);
    
    if (resultado.ciudades.empty()) {
        std::cout << "Error: Ciudad '" << targetCity << "' no encontrada en el sistema." << std::endl;
    } else {
        printResultado(resultado, 2);
    }
    
    pauseForUser();
}

void InterfazUsuario::masDistante() {
    std::cout << "\n============== CIUDADES MÁS DISTANTES ==================" << std::endl;
    std::cout << "Calculando el par de ciudades más distantes..." << std::endl;
    
    QueryResult resultado = analyzer->ciudadesDistantes();
    printResultado(resultado, 3);
    pauseForUser();
}

void InterfazUsuario::menosDistante() {
    std::cout << "\n============== CIUDADES MENOS DISTANTES ================" << std::endl;
    std::cout << "Calculando el par de ciudades menos distantes..." << std::endl;
    
    QueryResult resultado = analyzer->findLeastDistantCities();
    printResultado(resultado, 4);
    pauseForUser();
}

void InterfazUsuario::tiemposPromedio() {
    std::cout << "\n========== RANKING POR TIEMPO PROMEDIO =================" << std::endl;
    std::cout << "Calculando ranking de ciudades por tiempo promedio..." << std::endl;
    
    auto ranking = analyzer->getCitiesRankedByAvgTime();
    
    std::cout << "\nRanking de ciudades (orden creciente por tiempo promedio):" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    std::cout << std::left << std::setw(25) << "Ciudad" << std::setw(20) << "Tiempo Promedio" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    for (const auto& entry : ranking) {
        std::cout << std::left << std::setw(25) << entry.first 
                  << std::fixed << std::setprecision(2) << entry.second << std::endl;
    }
    
    std::cout << std::string(60, '-') << std::endl;
    pauseForUser();
}

void InterfazUsuario::printResultado(const QueryResult& resultado, int queryNumber) {
    std::cout << "\n--- RESULTADO ---" << std::endl;
    
    switch (queryNumber) {
        case 1:
            std::cout << "Centro(s) de distribución más efectivo(s):" << std::endl;
            for (const std::string& city : resultado.ciudades) {
                std::cout << "- " << city << std::endl;
            }
            std::cout << "Tiempo total de distribución: " << resultado.distance << " unidades" << std::endl;
            break;
            
        case 2:
            std::cout << "Mejor(es) ciudad(es) para despacho:" << std::endl;
            for (const std::string& city : resultado.ciudades) {
                std::cout << "- " << city << std::endl;
            }
            std::cout << "Tiempo de viaje: " << resultado.distance << " unidades" << std::endl;
            if (!resultado.path.empty()) {
                std::cout << "Ruta a seguir: ";
                printPath(resultado.path);
            }
            break;
            
        case 3:
            std::cout << "Par(es) de ciudades más distantes:" << std::endl;
            for (size_t i = 0; i < resultado.ciudades.size(); i += 2) {
                if (i + 1 < resultado.ciudades.size()) {
                    std::cout << "- " << resultado.ciudades[i] << " -> " << resultado.ciudades[i+1] << std::endl;
                }
            }
            std::cout << "Distancia máxima: " << resultado.distance << " unidades" << std::endl;
            if (!resultado.path.empty()) {
                std::cout << "Ruta del primer par: ";
                printPath(resultado.path);
            }
            break;
            
        case 4:
            std::cout << "Par(es) de ciudades menos distantes:" << std::endl;
            for (size_t i = 0; i < resultado.ciudades.size(); i += 2) {
                if (i + 1 < resultado.ciudades.size()) {
                    std::cout << "- " << resultado.ciudades[i] << " -> " << resultado.ciudades[i+1] << std::endl;
                }
            }
            std::cout << "Distancia mínima: " << resultado.distance << " unidades" << std::endl;
            if (!resultado.path.empty()) {
                std::cout << "Ruta del primer par: ";
                printPath(resultado.path);
            }
            break;
    }
}

void InterfazUsuario::printPath(const std::vector<std::string>& path) {
    for (size_t i = 0; i < path.size(); i++) {
        std::cout << path[i];
        if (i < path.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

int InterfazUsuario::getUserInput() {
    int input;
    while (!(std::cin >> input)) {
        std::cout << "Entrada inválida. Por favor, ingrese un número: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return input;
}

std::string InterfazUsuario::getUserString(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

void InterfazUsuario::pauseForUser() {
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}