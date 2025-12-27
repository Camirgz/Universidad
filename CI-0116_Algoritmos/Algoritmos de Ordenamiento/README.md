# Tarea I 

## Información General

- **Curso:** CI-0116 Análisis de Algoritmos y Estructuras de Datos
- **Ciclo:** I-2025
- **Profesor:** Dr. Allan Berrocal Rojas
- **Estudiante:** Camila Rodríguez Águila
- **Carné:** C36624

Esta tarea consiste en la implementación de seis algoritmos de ordenamiento y sus respectivos análisis de rendimiento. Se incluye también un reporte técnico con los resultados y gráficas comparativas.

## Algoritmos implementados

- Ordenamiento por Selección (Selection Sort)
- Ordenamiento por Inserción (Insertion Sort)
- Ordenamiento por Mezcla (Merge Sort)
- Ordenamiento por Montículos (Heapsort)
- Ordenamiento Rápido (Quicksort)
- Ordenamiento por Residuos (Radix Sort)

## Estructura del Proyecto

```
tareas_programadas/
└── tp1/
    ├── .vscode/
    ├── doc/
    │   └── ReporteIEEE.pdf
    ├── source/
    │   ├── ControladorArrays.cpp
    │   ├── ControladorArrays.hpp
    │   ├── Ordenador.cpp
    │   ├── Ordenador.hpp
    │   ├── main.cpp
    │   └── programa
    ├── tests/
    │   ├── out1.txt
    │   ├── out2.txt
    │   ├── out3.txt
    │   ├── README.md
    │   └── Pruebas.sh
    └── README.md

```

## Instrucciones para Compilar

Desde la carpeta `source/`, usar el siguiente comando:

```bash
 g++ main.cpp ControladorArrays.cpp Ordenador.cpp -o programa
 ./programa
```

El programa imprimirá los tiempos de ejecución para cada algoritmo en diferentes tamaños de arreglo, así como la verificación del ordenamiento y los datos del estudiante.

## Resultados

Los resultados experimentales incluyen:

- Tiempos de ejecución individuales (3 corridas por tamaño de entrada).
- Promedios por algoritmo y tamaño.
- Gráficas individuales y comparativas.
- Análisis de eficiencia teórica vs observada.

Toda esta información se encuentra en el documento `Reporte.pdf` dentro del directorio `doc/`.
