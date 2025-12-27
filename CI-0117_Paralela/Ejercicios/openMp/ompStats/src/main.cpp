// Copyright 2024 ECCI-UCR CC-BY 4.0

#include <iostream>   // Para entrada y salida estándar
#include <string>     // Para manejar cadenas
#include <vector>     // Para usar el contenedor vector

#include "stats.hpp"  // Se asume que contiene las funciones: minimum, maximum, average, std_dev, median

// Declaración de funciones plantilla para analizar datos de diferentes tipos
template <typename Type> int analyze();
template <typename Type> int analyze(std::vector<Type>& values);

int main() {
  std::string type; // Variable para guardar el tipo de dato ingresado

  if (std::cin >> type) { // Lee el tipo desde la entrada estándar
    // Según el tipo leído, llama a la función analyze correspondiente
    if (type == "short") return analyze<short>();
    if (type == "ushort") return analyze<unsigned short>();
    if (type == "int") return analyze<int>();
    if (type == "uint") return analyze<unsigned>();
    if (type == "long") return analyze<long>();
    if (type == "ulong") return analyze<unsigned long>();
    if (type == "double") return analyze<double>();
  }

  // Si no se reconoció ningún tipo, termina sin hacer nada
  return 0;
}

// Función plantilla que lee datos del tipo especificado y los almacena en un vector
template <typename Type> int analyze() {
  std::vector<Type> values;  // Vector para almacenar los valores
  Type value = Type();       // Variable temporal para leer cada dato

  // Lee valores desde la entrada estándar hasta que no haya más datos
  while (std::cin >> value) {
    values.push_back(value); // Añade el valor al vector
  }

  // Llama a la función que realiza el análisis estadístico
  return analyze(values);
}

// Función plantilla que realiza el análisis estadístico sobre un vector de datos
template <typename Type> int analyze(std::vector<Type>& values) {
  if (values.size() > 0) { // Verifica que haya datos

    // Imprime estadísticas básicas usando funciones definidas en stats.hpp
    std::cout << "Count  : " << values.size() << std::endl;
    std::cout << "Minimum: " << minimum(values) << std::endl;
    std::cout << "Maximum: " << maximum(values) << std::endl;
    std::cout << "Average: " << average(values) << std::endl;
    std::cout << "Std.Dev: " << std_dev(values) << std::endl;
    std::cout << "Median : " << median(values) << std::endl;
  }

  return 0; // Retorna 0 indicando que todo salió bien
}
