
# Simulación Concurrente de Difusión de Calor

---

## Descripción del problema a resolver

Este programa simula la difusión de calor en una placa utilizando la ecuación del calor y técnicas de programación concurrente. El objetivo es calcular la evolución de la temperatura en una matriz hasta alcanzar un estado de equilibrio térmico (criterio de convergencia) definido por el usuario.

El simulador trabaja a partir de archivos de entrada binarios (denominados *job*), que contienen la configuración inicial de la placa. Utiliza múltiples hilos (`pthread`) para realizar los cálculos de manera paralela, lo que mejora el rendimiento en sistemas multinúcleo.

Incluye lectura y escritura de archivos binarios, manipulación de matrices, creación de reportes y el uso de argumentos desde la línea de comandos.

---

## Requisitos

- Compilador de C (GCC recomendado).
- Sistema operativo Linux (preferiblemente Debian o derivado).
- Makefile disponible en el directorio de trabajo.

---

## Instalación

1. Clonar el repositorio desde:  
   <https://github.com/Camirgz/Concurrente25A-Camila_Rodriguez.git>

---

## Manual de Uso

1. Diríjase al directorio del proyecto:  
   `Tareas/pThreads`

2. Compile el proyecto con:  
   ```bash
   make
   ```

3. Ejecute el simulador con la siguiente sintaxis:  
   ```bash
   ./bin/pThreads tests/job002b/job002.txt 2
   ```
   Donde:
   - `tests/job002b/job002.txt`: Archivo *job* de entrada.
   - `2`: Cantidad de hilos a utilizar.

---

## Resultados

Los resultados de la simulación se almacenan en una carpeta generada automáticamente. Esta carpeta se limpia y regenera en cada ejecución. Contiene:

- Archivos binarios con los resultados finales de temperatura.
- Un archivo resumen con el número de iteraciones requeridas por cada archivo de entrada.
- El tiempo de ejecución de cada simulación.

---

## Referencias de Librerías

- ISO/IEC. (1999). String handling in C (ISO/IEC 9899:1999). International Organization for Standardization.

- ISO/IEC. (1999). Error handling in C (ISO/IEC 9899:1999). International Organization for Standardization.

- IEEE & The Open Group. (2004). Directory handling in POSIX systems (IEEE Std 1003.1-2004). The Open Group.

- IEEE & The Open Group. (2004). System data types (IEEE Std 1003.1-2004). The Open Group.

- IEEE & The Open Group. (2004). File status and attributes (IEEE Std 1003.1-2004). The Open Group.

- IEEE & The Open Group. (2004). UNIX standard definitions (IEEE Std 1003.1-2004). The Open Group.

- ISO/IEC. (1999). Fixed width integer types (ISO/IEC 9899:1999). International Organization for Standardization.

---

## Contacto

**Correo Universitario:**  
[camila.rodriguezaguila@ucr.ac.cr](mailto:camila.rodriguezaguila@ucr.ac.cr)

**Correo Personal:**  
[camila.rodriguez.aguila@gmail.com](mailto:camila.rodriguez.aguila@gmail.com)

---

## Créditos

Este proyecto fue desarrollado con el apoyo de **Microsoft Copilot**, utilizado para tareas de depuración y mejoras menores en el código fuente.
