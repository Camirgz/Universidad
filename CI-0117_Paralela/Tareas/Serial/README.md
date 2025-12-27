
# Descripción del problema a resolver

---

Este programa simula la difusión de calor en una placa utilizando una fórmula matemática. Se basa en la ecuación del calor y permite calcular la evolución de la temperatura en una matriz hasta alcanzar un criterio de convergencia definido por el usuario.

El simulador lee los parámetros desde un archivo de entrada (job) que contiene la configuración de la simulación, estos son archivos binarios con  los datos iniciales de la placa.

La simulación incluye la lectura de archivos, manipulación de matrices, y la generación de reportes. Además, de la utilización argumentos de línea de comandos para personalizar la ejecución del programa.

## Requisitos

---

Compilador para C, puede ser GCC, además ejecutar en un entorno Linux, preferiblemente Debian

## Instalación

Clonar repositorio desde: <https://github.com/Camirgz/Concurrente25A-Camila_Rodriguez.git>

## Manual de Uso

---

1. Diríjase a ```Tareas/Serial```
2. Ejecutar el programa utilice primero ```make```
3. Posteriormente utilice la siguiente configuración

    ```bash
    ./bin/Serial tests/job002.txt
    ```

## Resultados

Los resultados de la difusión de calor se almacenan en una carpeta que se crea/limpia por ejecución, estos son archivos binarios que tienen como nombre el original y la cantidad de iteraciones que fueron necesarias para crear un balance entre estos

Además se genera un archivo de reporte estilo resumen de la cantidad de iteraciones por archivo y el tiempo de ejecución de las mismas

## Referencias de Librerías

---

ISO/IEC. (1999). Programming languages — C standard library (ISO/IEC 9899:1999). International Organization for Standardization. <https://en.cppreference.com/w/c/header/stdio>

ISO/IEC. (1999). Standard library header stdlib.h (ISO/IEC 9899:1999). International Organization for Standardization. <https://www.tutorialspoint.com/header-files-stdio-h-and-stdlib-h-in-c>

ISO/IEC. (1999). String handling in C (ISO/IEC 9899:1999). International Organization for Standardization.

ISO/IEC. (1999). Error handling in C (ISO/IEC 9899:1999). International Organization for Standardization.

IEEE & The Open Group. (2004). Directory handling in POSIX systems (IEEE Std 1003.1-2004). The Open Group.

IEEE & The Open Group. (2004). System data types (IEEE Std 1003.1-2004). The Open Group.

IEEE & The Open Group. (2004). File status and attributes (IEEE Std 1003.1-2004). The Open Group.

IEEE & The Open Group. (2004). UNIX standard definitions (IEEE Std 1003.1-2004). The Open Group.

ISO/IEC. (1999). Fixed width integer types (ISO/IEC 9899:1999). International Organization for Standardization.

## Contacto

---

**eMail Universitario:** [camila.rodriguezaguila@ucr.ac.cr](mailto:camila.rodriguezaguila@ucr.ac.cr)

**eMail Personal:** [camila.rodriguez.aguila@gmail.com](mailto:camila.rodriguez.aguila@gmail.com)

### Créditos

---

Este proyecto fue desarrollado con la ayuda de Microsoft Copilot, este ayudó al proceso de debuggeo y arreglos menores, así como mejora del mismo.
