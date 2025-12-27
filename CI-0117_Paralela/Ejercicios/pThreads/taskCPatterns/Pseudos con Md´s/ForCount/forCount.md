### 1. Valor máximo posible de `count` (10000)
El valor más grande que `count` podría alcanzar es **10000** (100 hilos × 100 incrementos cada uno).

**Ruta de ejecución donde ocurre:**
- Todos los incrementos se ejecutan en serie (sin solapamiento), donde cada hilo completa su ciclo `for` completo antes de que otro hilo comience. Esto requiere que el scheduler ejecute los hilos uno tras otro sin interrupciones.

```
Hilo1: temp=0 → count=1 → temp=1 → count=2 → ... → count=100
Hilo2: temp=100 → count=101 → ... → count=200
...
Hilo100: temp=9900 → count=9901 → ... → count=10000
```

---

### 2. Valor mínimo posible de `count` (100)
El valor más pequeño que `count` podría alcanzar es **100**.

**Ruta de ejecución donde ocurre:**
- Todos los hilos leen el valor inicial `temp=0` simultáneamente antes de que cualquiera escriba en `count` (condición de carrera). Cada hilo escribe `count=temp+1=1`, pero como ocurren en paralelo, muchos incrementos se pierden.

```
Todos los hilos ejecutan en paralelo:
Paso 1: 100 hilos leen temp=0 (valor inicial)
Paso 2: 100 hilos escriben count=temp+1=1
(El valor final es 1, pero cada iteración subsiguiente del for repite el problema)
```

**Explicación detallada del mínimo:**
Cada iteración del `for` puede sufrir la misma condición de carrera. En el peor caso:
- En cada una de las 100 iteraciones del `for`, los 100 hilos leen el mismo valor de `count` (por ejemplo, `temp=0` en la primera iteración).
- Todos escriben `count=1`, pero solo 1 escritura persiste (las demás se sobrescriben).
- Esto se repite para cada iteración, resultando en solo 100 incrementos efectivos (1 por iteración del `for`).

---

### Nota clave:
- **Máximo (10000)**: Requiere ejecución secuencial estricta (sin concurrencia real).
- **Mínimo (100)**: Ocurre cuando todas las operaciones `temp=count` y `count=temp+1` se intercalan de la peor manera posible (máxima contención).
- En la práctica, es más probable obtener valores intermedios debido al scheduling impredecible.
```