### Simulador SQL en C++
---
Este proyecto es un simulador de SQL implementado en C++. Soporta varias funcionalidades básicas de SQL como consultas `SELECT`, `WHERE`, `ORDER BY`, y funciones de agregación como `MIN`, `MAX`, `COUNT`, `SUM` y `AVG`.

## Funcionalidades Soportadas

El simulador SQL actualmente admite las siguientes funcionalidades:

- **`SELECT`**: Selección de columnas específicas en una consulta.
- **`SELECT DISTINCT`**: Selección de columnas eliminando valores duplicados.
- **`WHERE`**: Filtrado de resultados basado en condiciones.
- **`ORDER BY`**: Ordenamiento de los resultados de una consulta.
- **`AND`, `OR`, `NOT`**: Operadores lógicos para combinar condiciones en las consultas.
- **Funciones de Agregación**:
  - **`MIN(columna)`**: Devuelve el valor mínimo de la columna seleccionada.
  - **`MAX(columna)`**: Devuelve el valor máximo de la columna seleccionada.
  - **`COUNT(columna)`**: Cuenta el número de elementos en la columna.
  - **`SUM(columna)`**: Suma los valores de una columna.
  - **`AVG(columna)`**: Calcula el promedio de una columna.


## Requisitos

- **C++**: Se necesita un compilador compatible con C++11 o superior.
- **Shell**: Para ejecutar el script de compilación.

## Ejecución del Simulador

Para ejecutar el simulador, sigue estos pasos:

1. Clonar el repositorio:
   ```bash
   git clone https://github.com/Camirgz/SimuladorSQL.git
   cd SimuladorSQL/
2. Dar Permisos de ejecución al script de compilación
    ```bash
    chmod +x Compilaciones.sh
3. Ejecutar script
    ```bash
    ./Compilaciones.sh
