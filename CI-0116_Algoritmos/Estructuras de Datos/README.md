# Tarea II

## Información General

- **Curso:** CI-0116 Análisis de Algoritmos y Estructuras de Datos
- **Ciclo:** I-2025
- **Profesor:** Dr. Allan Berrocal Rojas
- **Estudiante:** Camila Rodríguez Águila
- **Carné:** C36624

Esta tarea consiste en la implementación de cuatro estructuras de datos y sus respectivos análisis de desempeño, a través de la inserción (ordenada y aleatoria) y la búsqueda de elementos (ordenados y aleatorios). Se incluye también un reporte técnico con los resultados y gráficas comparativas.

## Algoritmos implementados
- BinarySearchTree.hpp - Árbol de Búsqueda Binaria
- ChainedHashTable.hpp - Tablas de Dispersión
- RedBlackTree.hpp - Árbol Rojinegro
- SinglyLinkedList.hpp - Lista Simplemente Enlazada

## Estructura del Proyecto

```bash
doc/
├── grphs/
│   ├── grphs.ipynb
│   └── README.md
├── imgs/
│   └── imgs.jpg
└── doc.tex

source/
├── BinarySearchTree.hpp
├── ChainedHashTable.hpp
├── Controlador.cpp
├── Controlador.hpp
├── DoublyLinkedList.hpp
├── GenerarArray.hpp
├── main.cpp
├── RedBlackTree.hpp
├── SinglyLinkedList.hpp
└── Student.hpp

tests/
└── tests.sh

Enunciado.pdf
README.md

```

## Instrucciones para Compilar 3 Veces

Desde , `Tareas_Programadas/tp2` , usar el siguiente comando:

```bash
 make clean
 make exe
```

### Comandos del Makefile

- `make` o `make all`: compila los archivos y genera el ejecutable.
- `make exe`: compila y ejecuta el programa.
- `make clean`: borra los archivos compilados.
- `make tests`: ejecuta el programa 3 veces y guarda las salidas en `tests/`

## Resultados

Los resultados experimentales incluyen:

- Tiempos de ejecución individuales (3 corridas por tamaño de entrada).
- Promedios por algoritmo y tamaño.
- Gráficas individuales y comparativas.
- Análisis de eficiencia teórica vs observada.

Toda esta información se encuentra en el documento `Reporte.pdf` dentro del directorio `doc/`.

