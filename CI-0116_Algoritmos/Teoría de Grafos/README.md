# Sistema Nacional de Tipificación de Emergencias Potenciales (SiNTiEmPo)

## Descripción

Este proyecto implementa un sistema de análisis de rutas para centros de emergencia utilizando teoría de grafos y algoritmos eficientes. El sistema permite analizar la conectividad entre ciudades y optimizar la distribución de recursos en situaciones de emergencia.

## Características Principales

- **Análisis de grafos dirigidos ponderados** usando el algoritmo Floyd-Warshall
- **Interfaz de usuario interactiva** con menú de opciones
- **Carga de datos desde archivos CSV**
- **Cinco consultas principales** para optimización de recursos:
  1. Centro de distribución más efectivo
  2. Mejor ciudad para despacho hacia un objetivo específico
  3. Par de ciudades más distantes
  4. Par de ciudades menos distantes
  5. Ranking de ciudades por tiempo promedio

## Arquitectura del Sistema

### Clases Principales

1. **Grafo**: Representa el grafo dirigido ponderado con ciudades como vértices
2. **FileReader**: Maneja la lectura de archivos CSV y construcción del grafo
3. **AnalizadorGrafo**: Implementa algoritmos de análisis (Floyd-Warshall)
4. **InterfazUsuario**: Proporciona la interfaz de usuario interactiva

### Algoritmo Utilizado

El sistema utiliza el **algoritmo Floyd-Warshall** con complejidad O(V³) para:
- Encontrar todos los caminos más cortos entre pares de vértices
- Calcular distancias mínimas eficientemente
- Reconstruir rutas óptimas

## Compilación

### Requisitos

- Compilador g++ con soporte para C++11 o superior
- Make 

### Opciones de compilación

**Usando Makefile (recomendado):**

```bash
make
```


## Ejecución

### Uso básico

```bash
./sintiempo archivo.csv
```

### Ejemplos con archivos de prueba

```bash
# Archivo pequeño
./bin/sintiempo tests/input_small.csv

```

## Formato de Archivo CSV

El archivo de entrada debe tener el siguiente formato:

```csv
SourceId,SourceName,TargetId,TargetName,peso
0,Ciudad1,1,Ciudad2,5
1,Ciudad2,2,Ciudad3,8
...
```


## Funcionalidades del Sistema

### Menú Principal

1. **Centro de distribución más efectivo**
   - Encuentra la ciudad desde donde se puede distribuir equipo a todas las demás con menor tiempo total
   - Utiliza la suma de distancias mínimas desde cada ciudad

2. **Mejor ciudad para despacho hacia objetivo específico**
   - Dada una ciudad objetivo, encuentra la mejor ciudad origen
   - Muestra la ruta óptima y el tiempo de viaje

3. **Par de ciudades más distantes**
   - Identifica las ciudades que están más lejos entre sí
   - Proporciona la ruta más corta entre ellas

4. **Par de ciudades menos distantes**
   - Encuentra las ciudades más cercanas (excluyendo la misma ciudad)
   - Útil para identificar conexiones directas importantes

5. **Ranking por tiempo promedio**
   - Lista todas las ciudades ordenadas por su tiempo promedio hacia las demás
   - Ayuda a identificar centros estratégicos

## Análisis de Complejidad

- **Tiempo**: O(V³) para el algoritmo Floyd-Warshall
- **Espacio**: O(V²) para almacenar matrices de distancias y reconstrucción de caminos
- **Donde V** es el número de vértices (ciudades) en el grafo

## Pruebas y Validación

### Archivos de prueba incluidos en carpeta `tests\`:

- `input_small.csv`: Grafo pequeño para validación básica
- `input_medium.csv`: Grafo mediano para pruebas intermedias  
- `input_large.csv`: Grafo grande para pruebas de rendimiento


## Estructura de Directorios

```
tp3/
├── doc/
│   ├── Resultados/
│   │   ├── Resumenes/
│   │   ├── Salidas/
│   │   ├── Anexo General.docx
│   │   ├── Anexo General.pdf
│   │   └── Reporte.pdf
├── source/
│   ├── AnalizadorGrafo.cpp
│   ├── AnalizadorGrafo.h
│   ├── FileReader.cpp
│   ├── FileReader.h
│   ├── Grafo.cpp
│   ├── Grafo.h
│   ├── InterfazUsuario.cpp
│   ├── InterfazUsuario.h
│   └── main.cpp
├── tests/
│   ├── input_large.csv
│   ├── input_medium.csv
│   └── input_small.csv
├── Makefile
└── README.md
```

## Limitaciones Conocidas

- El sistema asume que el grafo es conexo (todas las ciudades son alcanzables)
- Los pesos de las aristas deben ser positivos
- La entrada debe estar en formato CSV válido

## Autora
Camila Rodríguez Águila - C36624
Desarrollado como parte del curso CI-0116 Análisis de Algoritmos y Estructuras de Datos, Universidad de Costa Rica.

## Licencia

Este proyecto es desarrollado con fines académicos.