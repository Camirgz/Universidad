#include "tests.h"
#include <iostream>
#include <string>

#ifdef _WIN32
    #include <windows.h>

    void color(std::string color, std::string line, bool newLine) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        int col = 7;  // Default to white

        if (color == "blue") col = 1;
        else if (color == "green") col = 2;
        else if (color == "cyan") col = 3;
        else if (color == "red") col = 4;
        else if (color == "magenta") col = 5;
        else if (color == "yellow") col = 6;

        SetConsoleTextAttribute(hConsole, col);
        std::cout << line;
        if (newLine) {
            std::cout << std::endl;
        }
        SetConsoleTextAttribute(hConsole, 7); // Reset to default color
    }
#else
    void color(std::string color, std::string line, bool newLine) {
        std::string col = "\033[0m"; // Default to reset color

        if (color == "blue") col = "\033[0;34m";
        else if (color == "green") col = "\033[0;32m";
        else if (color == "cyan") col = "\033[0;36m";
        else if (color == "red") col = "\033[0;31m";
        else if (color == "magenta") col = "\033[0;35m";
        else if (color == "yellow") col = "\033[0;33m";

        std::cout << col << line << "\033[0m";
        if (newLine) {
            std::cout << std::endl;
        }
    }
#endif

// Definición de las funciones `assertEquals`:

// Para comparar cadenas
bool assertEquals(std::string resultadoEsperado, std::string resultadoReal, std::string nombrePrueba) {
    if (resultadoEsperado == resultadoReal) {
        color("green", nombrePrueba + " OK", true);
        return true;
    } else {
        color("red", nombrePrueba + " ERROR", true);
        return false;
    }
}

// Para comparar enteros
bool assertEquals(int resultadoEsperado, int resultadoReal, std::string nombrePrueba) {
    if (resultadoEsperado == resultadoReal) {
        color("green", nombrePrueba + " OK", true);
        return true;
    } else {
        color("red", nombrePrueba + " ERROR", true);
        return false;
    }
}

// Para comparar arreglos
bool assertEquals(int resultadoEsperado[], int resultadoReal[], int n, std::string nombrePrueba) {
    for (int i = 0; i < n; ++i) {
        if (resultadoEsperado[i] != resultadoReal[i]) {
            color("red", nombrePrueba + " ERROR", true);
            return false;
        }
    }
    color("green", nombrePrueba + " OK", true);
    return true;
}
