# Sistema de Memoria Virtual con Multiprocesamiento

Este proyecto implementa un sistema completo de memoria virtual con soporte para multiprocesamiento mediante threads (pthread). Simula el funcionamiento de varios procesos ejecutando programas en ensamblador, incluyendo paginación, TLB, caché de datos, dos algoritmos de reemplazo de páginas y manejo de fallos.

---

## **Descripción General**

El sistema implementa:

* Memoria virtual paginada: 1024 bytes por proceso (64 páginas de 16 bytes).
* Memoria física: 512 bytes (32 frames de 16 bytes).
* TLB de 4 entradas con reemplazo LRU.
* Caché de datos de 8 entradas con bloques de 4 bytes.
* MMU para traducción de direcciones lógicas a físicas.
* Dos algoritmos de reemplazo de páginas: Enhanced Second Chance y LRU.
* Procesos concurrentes mediante pthread.
* CPU simulado que ejecuta instrucciones en ensamblador.

---

## **Características Implementadas**

### Obligatorias

* Traducción de direcciones lógicas → físicas.
* Page faults.
* Algoritmo de reemplazo (Enhanced Second Chance).
* Mínimo 2 procesos concurrentes.
* Programas con loops y saltos.
* Tablas de página con bits V/D/R.

### Puntos Extra

* TLB con reemplazo LRU y estadísticas de hits/misses.
* Caché de datos asociativa para acelerar accesos a memoria.
* Segundo algoritmo de reemplazo (LRU) con selección en tiempo de ejecución.
* Estadísticas completas de TLB y caché de datos.

---

## **Arquitectura**

Componentes principales:

1. CPU (interpreta instrucciones).
2. MMU (traducción de direcciones).
3. TLB (caché de traducciones de páginas).
4. Caché de Datos (caché asociativa para datos).
5. Tablas de página por proceso.
6. Memoria física.
7. Enhanced Second Chance (reemplazo de páginas).
8. LRU (algoritmo alternativo de reemplazo).

---

## **Archivos Principales**

Incluye archivos como:

* `virtual_memory_system.h`, `cpu.cpp`, `mmu.cpp`, `memory.cpp`, `data_cache.cpp`, `process.cpp`, `tlb_pagetable.cpp`, `main.cpp`.
* Programas de ejemplo (`program1.txt` a `program4.txt`).
* Makefile.

---

## **Compilación y Ejecución**

### Requisitos

* Compilador g++ con soporte para C++11
* pthread (incluido en sistemas Unix/Linux)

### Compilación

Desde el directorio raíz del proyecto:

```bash
cd tests
make
```

Esto compilará el proyecto con las siguientes opciones:
* `-std=c++11`: Estándar C++11
* `-pthread`: Soporte para threads
* `-Wall -Wextra`: Advertencias extendidas
* `-g`: Información de depuración

Para limpiar archivos compilados:

```bash
make clean
```

Para recompilar desde cero:

```bash
make rebuild
```

### Ejecución Manual

Después de compilar, el ejecutable estará en `bin/vm_system`.

Con Enhanced Second Chance (por defecto):
```bash
./bin/vm_system program1.txt program2.txt
```

Con algoritmo LRU:
```bash
./bin/vm_system --lru program1.txt program2.txt
```

Puede ejecutar de 1 a 4 programas simultáneamente.

### Ejecución con Make

El Makefile incluye varios targets para facilitar la ejecución:

```bash
make run              # Ejecutar con 1 programa
make run-two          # Ejecutar con 2 programas (mínimo requerido)
make run-three        # Ejecutar con 3 programas
make run-multi        # Ejecutar con 4 programas (máximo)
make run-lru          # Ejecutar con 2 programas usando LRU
make run-lru-multi    # Ejecutar con 4 programas usando LRU
```

### Pruebas Automatizadas

El proyecto incluye dos formas de ejecutar pruebas:

#### Opción 1: Con Make

```bash
make test
```

Ejecuta pruebas rápidas con 1 y 2 procesos, mostrando las primeras 20 líneas de salida.

#### Opción 2: Script de Pruebas Completo

```bash
chmod +x run_tests.sh    # Solo necesario la primera vez
./run_tests.sh
```

Este script ejecuta automáticamente:

1. Limpia compilaciones anteriores
2. Compila el proyecto completo
3. Ejecuta 4 pruebas diferentes:
   * Prueba 1: Proceso individual
   * Prueba 2: Dos procesos (mínimo requerido)
   * Prueba 3: Tres procesos
   * Prueba 4: Cuatro procesos (máximo)

El script incluye:
* Verificación de archivos necesarios
* Mensajes informativos con colores
* Detección automática de errores de compilación

### Verificación del Sistema

Para verificar que todos los archivos necesarios están presentes:

```bash
make check
```

Para ver la configuración del sistema:

```bash
make info
```

Para ver todos los targets disponibles:

```bash
make help
```

---

## **Formato de Programas**

Los programas están en ensamblador simple con instrucciones como:
MOV, LD, ST, ADD, SUB, MUL, DIV, INC, DEC, CMP, JMP, JE, JNE, HALT.

---

## **Salida del Sistema**

Durante la ejecución se muestran:

* Inicio y finalización de procesos.
* Registros finales de cada proceso.
* Estadísticas de memoria (accesos, page faults).
* Estadísticas del TLB (hits, misses, tasa de hits).
* Estadísticas de caché de datos (hits, misses, tasa de hits).
* Estado de la memoria física.
* Algoritmo de reemplazo utilizado.

---

## **Especificaciones Técnicas**

### Memoria Virtual

* 1024 bytes por proceso (64 páginas de 16 bytes).
* 6 bits de VPN, 4 bits de offset.

### Memoria Física

* 512 bytes, 32 frames de 16 bytes.

### TLB

* 4 entradas, reemplazo LRU.

### Caché de Datos

* 8 entradas, bloques de 4 bytes, reemplazo LRU.

### Reemplazo de Páginas

* Enhanced Second Chance con clasificación por bits R y D.
* LRU (Least Recently Used) como algoritmo alternativo.

## **Resultados Esperados**

* Ejecución concurrente estable.
* Page faults controlados.
* Mejora de rendimiento con TLB y caché de datos.
* TLB Hit Rate típico: > 60%.
* Caché Hit Rate típico: > 50%.

---

## **Autoras**

* Camila Rodríguez - C36624
* Yosery Zheng Lu - C38680

---