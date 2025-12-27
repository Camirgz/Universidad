## Reporte de optimizaciones

## Optimizaciones seriales

| Iter. | Etiqueta | Duración (s) | *Speedup* | Descripción corta                                           |
| ----- | -------- | ------------ | --------- | ----------------------------------------------------------- |
| 0     | Serial0  | Invalida     | 1.00      | Versión serial inicial (Tarea01) - Cerrado por cluster      |
| 1     | Serial1  | 2432         | 1.36      | *Double buffering* y un único buffer con *swap* de punteros |

### Versión serial original (Tarea01)

La versión original incluía:

* **malloc/free** y **memcpy** completos en cada iteración.
* Cálculo repetido de coeficientes dentro del *loop*.

### Iteración 1

**Optimización:**

* Introducción de *double buffering*: un solo buffer extra y, en lugar de `memcpy`, se intercambian punteros (`src` ↔ `dst`) tras cada iteración.
* Cálculo del coeficiente **una sola vez** antes del bucle.

```c
// swap de punteros en lugar de memcpy:
double *temp = src;
src = dst;
dst = temp;
```

**Resultado:** de **3 314 s** (\~55 min) a **2 432 s** (\~40.5 min), un *speedup* de **1.36×**.

---

## Optimizaciones concurrentes

| Iter. | Etiqueta  | Duración (s) | *Speedup* | Eficiencia | Descripción corta                                  |
| ----- | --------- | ------------ | --------- | ---------- | -------------------------------------------------- |
| –     | Serial I  | 2432         | 1.00      | 1.00       | Versión serial final                               |
| 1     | ConcFinal | 697          | 3.49      | 0.11       | Paralelización equilibrada con lectura concurrente |

### Versión concurrente final (Tarea03)

**Optimización:**

* Paralelizar la etapa de lectura y creación de estructuras `Plate` desde `main`, asignando cada línea de job a un hilo sin bloqueos en el bucle interior.
* Preasignar buffers privados por hilo para eliminar `malloc/free` dentro de la simulación.
* Crear los `pthread` **una sola vez** al inicio y reaprovecharlos hasta el final (uso de barriers en lugar de *locks* frecuentes).

**Resultado:** de **2 432 s** (\~40.5 min) a **697 s** (\~11.6 min), obteniendo un *speedup* de **3.49×** y una eficiencia (en 32 hilos teóricos) de **≈ 0.11**.

---

### Comparación de optimizaciones

| Versión         | Duración (s) | *Speedup* sobre Serial0 |
| --------------- | ------------ | ----------------------- |
| Serial 1        | 3 314        | 1.00                    |
| ConcFinal (32t) | 697          | 4.76                    |

---

### Comparación del grado de concurrencia

> En **Job 20**, el balance adecuado entre paralelismo en I/O (lectura de plates) y minimización de *overhead* de sincronización permitió reducir el tiempo de \~40 min a menos de 12 min, manteniéndose por debajo de la hora límite incluso para el caso más grande.

---

### Consideraciones sobre el mapeo de tareas: estático vs dinámico

Durante el desarrollo concurrente, se exploraron inicialmente dos enfoques para distribuir las tareas de simulación entre hilos:

#### Mapeo dinámico (fallido)

Se implementó un esquema dinámico en el cual los hilos tomaban placas desde una cola compartida utilizando exclusión mutua (`mutex`). La idea era permitir un balanceo de carga natural: que los hilos rápidos procesaran más placas y los lentos menos.

Sin embargo, este enfoque introdujo varios problemas:

* **El tiempo total aumentó** considerablemente (por ejemplo, de \~697 s a \~789 s en `job20`).
* El acceso constante a la cola de trabajo compartida generó **contenidos en los `mutex`**, haciendo que los hilos esperaran por turnos para obtener trabajo.
* Hubo **sobrecarga por sincronización**, especialmente notoria al escalar a más de 8 hilos.
* La complejidad del código aumentó sin ofrecer beneficios tangibles.

#### Estático (utilizado en la versión final)

El enfoque adoptado en la versión final fue un **mapeo estático**, donde:

* Cada hilo recibe una asignación fija de placas al inicio.
* No existen accesos compartidos ni estructuras que requieran sincronización.
* Se evita completamente el uso de `mutex` dentro del bucle de simulación.

Este método resultó claramente superior:

* Redujo el tiempo de ejecución hasta los **697 s**, sin afectar la corrección.
* Eliminó el *overhead* de coordinación entre hilos.
* Facilitó la implementación y permitió una **ejecución completamente `lock-free`**.
* La eficiencia por hilo aumentó significativamente, aunque limitada por el paralelismo de datos.

---

### Conclusión

Aunque el mapeo dinámico puede ser útil cuando las tareas tienen **tiempos de ejecución muy desiguales**, en este caso particular:

* Las placas eran **homogéneas** en tamaño y tiempo.
* El costo de la sincronización superó cualquier posible ganancia.
* El mapeo estático fue más **eficiente, limpio y fácil de mantener**.

Por lo tanto, se optó por este último para la versión final del simulador concurrente.

## Indeterminismo en la ejecución
Durante la ejecución del programa, se observó un comportamiento indeterminado en ciertos aspectos del flujo, especialmente cuando se procesan múltiples placas con diferentes tamaños y cantidades de iteraciones requeridas. Este indeterminismo se manifiesta principalmente en dos formas:

### Orden de lectura y procesamiento de archivos:
Aunque las placas se listan en un orden específico en el archivo de trabajo (job.txt), el programa puede no procesarlas estrictamente en ese orden al utilizar hilos para paralelizar la carga o simulación.

### Duración de las simulaciones por placa:
Cada placa requiere un número distinto de iteraciones para estabilizarse. Esta cantidad distinta de iteraciones causa que el tiempo de finalización de cada simulación varíe, y puede cambiar de una ejecución a otra si hay factores externos como la carga del sistema, planificación del sistema operativo o el uso de múltiples hilos.

Por eso el orden de aparición de las salidas no siempre refleja el orden lógico del archivo de entrada. Aun así, el programa garantiza que cada placa es procesada y almacenada correctamente, independientemente del orden o del número de iteraciones que necesite.
