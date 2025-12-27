**Nota:**Este archivo es una recopilación de las respuestas a los ejercicios del archivo `Práctica.md`, recopilación ya que en cada carpeta en `Pseudos con Md´s`, cada subcarpeta incluye su propio `.md` de las respuestas

# 1. Execution Paths

### Caso 1: Thread A se ejecuta primero completamente
1. `thread_a`: x = 5
2. `thread_a`: print(x) → Salida: "5"
3. `thread_b`: x = 7

**Resultado final:**
- Valor de x: 7
- Salida estándar: "5"

### Caso 2: Thread B se ejecuta primero completamente
1. `thread_b`: x = 7
2. `thread_a`: x = 5
3. `thread_a`: print(x) → Salida: "5"

**Resultado final:**
- Valor de x: 5
- Salida estándar: "5"

### Caso 3: Ejecución intercalada 
1. `thread_a`: x = 5
2. `thread_b`: x = 7
3. `thread_a`: print(x) → Salida: "7"

**Resultado final:**
- Valor de x: 7
- Salida estándar: "7"

# 2. For Count

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

# 3. Signaling

#### 3.1. Solución para 2 hilos (a1 < b1)

- Semáforo `a1_ready` inicializado en 0 (bloqueado)
- `thread_a` ejecuta `a1` y luego libera el semáforo con `signal(a1_ready)`
- `thread_b` espera con `wait(a1_ready)` antes de ejecutar `b1`
`a1` siempre se ejecuta antes que `b1`.

---

#### 3.2. Solución para 3 hilos (a1 < b1 < c1)

1. `thread_a` ejecuta `a1` y señala `a1_ready`.
2. `thread_b` espera `a1_ready`, ejecuta `b1`, y señala `b1_ready`.
3. `thread_c` espera `b1_ready` antes de ejecutar `c1`.  
`a1 → b1 → c1`.

---

#### 3.3. Solución general para *w* hilos (a0 < a1 < ... < aw)

1. **Inicialización:**  
   - Semáforo `can_do_a[0]` se inicializa en 1 (para permitir que el primer hilo comience).
   - Los demás semáforos en el arreglo `can_do_a` se inicializan en 0 (bloqueados).

2. **Funcionamiento:**  
   - Cada hilo `i` espera su turno con `wait(can_do_a[i])`.
   - Tras ejecutar `statement a`, libera el semáforo del siguiente hilo con `signal(can_do_a[(i+1) % thread_count])`.

# 4. RendezVous

#### Explicación detallada:
1. **Semáforos inicializados en 0**:
   - `a1_ready`: Señalizado cuando `thread_a` completa `a1`.
   - `b1_ready`: Señalizado cuando `thread_b` completa `b1`.

2. **Flujo de ejecución**:
   - **Caso 1**: Si `thread_a` llega primero al rendezvous:
     - Ejecuta `a1` y señala `a1_ready`.
     - Se bloquea en `wait(b1_ready)` hasta que `thread_b` complete `b1` y señale `b1_ready`.
   - **Caso 2**: Si `thread_b` llega primero:
     - Ejecuta `b1` y señala `b1_ready`.
     - Se bloquea en `wait(a1_ready)` hasta que `thread_a` complete `a1`.

3. **Fijo:**:
   - **Ningún hilo avanza a `a2`/`b2`** sin que el otro haya completado su primera instrucción (`a1`/`b1`).
   - **Ausencia de deadlock**: Siempre hay señalización mutua.

# 4.1 ChessVous
### Solución para el Encuentro de Ajedrez (ChessVous)

La implementación garantiza que:
1. El árbitro ejecute `set_clock()` solo después de que ambos jugadores hayan ingresado (`enter_room()`).
2. Los jugadores ejecuten `play_chess()` solo después de que el árbitro haya configurado el reloj (`set_clock()`).

#### Explicación detallada:

1. **Semáforos utilizados**:
   - `players_ready`: Contador inicializado en 0. Incrementado por cada jugador al ingresar.
   - `clock_ready`: Semáforo binario inicializado en 0. Liberado por el árbitro tras configurar el reloj.

2. **Flujo de ejecución**:
   - **Jugadores**:
     ```pseudo
     enter_room()           // Paso 1: Ingresan al centro
     signal(players_ready)  // Paso 2: Notifican su llegada (incrementa el contador)
     wait(clock_ready)      // Paso 3: Esperan señal del árbitro
     play_chess()           // Paso 4: Inician la partida
     ```
   - **Árbitro**:
     ```pseudo
     enter_room()               // Paso A: Ingresa al centro
     wait(players_ready, 2)     // Paso B: Espera a 2 señales (ambos jugadores listos)
     set_clock()                // Paso C: Configura el reloj
     signal(clock_ready, 2)     // Paso D: Libera a ambos jugadores (2 señales)
 
# 5. SemMutex

#### 5.1. Solución Asimétrica

- El semáforo `can_access_count` actúa como **mutex** (inicializado en 1).  
- Solo un thread puede estar en la sección crítica (incrementando `count`) en cualquier momento.  

#### 5.2. Solución Simétrica (Generalizada para *N* hilos)

**Ventajas**:  
1. **Reutilizable**: El mismo código (`secondary`) se ejecuta en todos los hilos.  
2. **Escalable**: Funciona para cualquier número de hilos (`thread_count`).  
3. **Mantenible**: Cambios en la lógica de exclusión se aplican a todos los hilos.  

# 6. Multiplex

#### Explicación:
1. **Semáforo contador** (`can_skate`):  
   - Inicializado con `room_capacity` (ejemplo: 10 para una pista con capacidad de 10 patinadores).  
   - Cada `wait()` decrementa el contador (es como si le dieran un "permiso").  
   - Cada `signal()` lo incrementa (libera el permiso).  

2. **Comportamiento**:  
   - Si hay espacio (`can_skate > 0`), los patinadores entran inmediatamente.  
   - Si la pista está llena (`can_skate = 0`), nuevos patinadores esperan hasta que alguien salga (`signal`).  

3. **Garantías**:  
   - Máximo `room_capacity` hilos ejecutando `skate()` concurrentemente.  
   - Ausencia de inanición: Los patinadores entran en orden FIFO (si el semáforo es justo).  

#### Explicación:
1. **Semáforo contador** (`can_skate`):  
   - Inicializado con `room_capacity` (ejemplo: 10 para una pista con capacidad de 10 patinadores).  
   - Cada `wait()` decrementa el contador (es como si le dieran un "permiso").  
   - Cada `signal()` lo incrementa (libera el permiso).  

2. **Comportamiento**:  
   - Si hay espacio (`can_skate > 0`), los patinadores entran inmediatamente.  
   - Si la pista está llena (`can_skate = 0`), nuevos patinadores esperan hasta que alguien salga (`signal`).  

3. **Garantías**:  
   - Máximo `room_capacity` hilos ejecutando `skate()` concurrentemente.  
   - Ausencia de inanición: Los patinadores entran en orden FIFO (si el semáforo es justo).  

# 7. SemBarrier

### 7. Barrera con semáforos (barrier)

#### 7.1. Barrera de una pasada [sem_barrier_1pass]

**Mecanismo clave**:  
- El **último hilo** (que hace `count = thread_count`) libera `thread_count` señales del semáforo `barrier`.  
- **Problema**: No es reusable (el contador `count` no se reinicia).  

---

#### 7.2. Barrera reusable con torniquete [sem_barrier_reusable]
Solución mejorada con **dos torniquetes** (uno para entrar, otro para salir):


**Cómo funciona**:  
1. **Primer torniquete (`turnstile_in`)**:
   - Inicialmente bloqueado (`0`).  
   - El último hilo lo abre con `signal(turnstile_in)`, liberando a todos.  
2. **Segundo torniquete (`turnstile_out`)**:
   - Inicialmente abierto (`1`).  
   - El último hilo lo cierra para preparar la siguiente ronda.  

**Ventajas**:  
- **Reusabilidad**: El contador `count` se reinicia automáticamente.  
- **Justicia**: Los hilos pasan en orden (FIFO).  
- **Eficiencia**: Evita el "despertar en cascada" del enfoque anterior.  

**Flujo** (con 3 hilos):  
1. Todos ejecutan `Statement A`.  
2. El hilo 3 (último) abre `turnstile_in` → todos pasan a `Statement B`.  
3. El hilo 1 (último en salir) abre `turnstile_out` → prepara la siguiente iteración.  
