# Patrones básicos de concurrencia de tareas

El fin de la concurrencia de tareas es la correcta separación de asuntos. No busca tanto la optimización, sino que los entes realicen tareas distintas de forma correcta. Los problemas en esta categoría son de especial interés para la computación misma, dado que son aplicables a variedad de herramientas como sistemas operativos, motores de bases de datos, servidores web, entre otros. Típicamente los problemas en esta categoría buscan que la concurrencia de tareas genere resultados correctos a través de la aplicación de mecanismos de sincronización, por lo que se les suele también llamar *problemas de sincronización*.

## Rutas de ejecución [execution_paths]

Dos _threads_ ejecutan las siguientes tareas. Liste todas las rutas de ejecución indicando el valor final de la variable `x` y la salida estándar. Una *ruta de ejecución* (_execution path_) es una combinación de instrucciones que depende del orden en que sean ejecutadas.

## Rutas de ejecución extremas [for_count]

Suponga que el hilo de ejecución principal crea _w=100_ hilos secundarios con los siguientes códigos.

1. ¿Cuál es el valor más grande que la variable compartida `count` podría llegar a obtener? ¿En qué rutas de ejecución se alcanza este valor?

2. ¿Cuál es el menor valor que la variable compartida `count` podría llegar a obtener? ¿En qué rutas de ejecución se alcanza este valor?


## Avisar/notificar [signaling]

### 2 hilos

Haga que la instrucción `a1` se ejecute siempre antes que la instrucción `b1`. Esto es, que un hilo envíe una señal (aviso) a otro (_signaling_).

### 3 hilos

Haga que la instrucción `a1` se ejecute siempre antes que la instrucción `b1` y ésta siempre se ejecute antes que la instrucción `c1`. Este orden de ejecución puede abreviarse como `a1 < b1 < c1`.

### w hilos

Generalice el patrón de aviso (_signaling_) para dada una cantidad arbitraria `w` de hilos que ejecutan la instrucción `a`, lo hagan en el orden del número de hilo. Por ejemplo, si `ai` es la ejecución de la instrucción `statement a` por parte del hilo con número `i`, entonces se asegure que siempre se ejecute la secuencia `a0 < a1 < a2 < a3 < ... < aw`.

Una solución a este problema se había hecho antes en el curso ¿recuerda en cuál ejemplo?  
**Respuesta:**

## Encuentro (_rendezvous_)

Haga que la instrucción `a1` y `b1` se ejecuten siempre antes que las instrucciones `a2` y `b2`. Este problema tiene el nombre francés _rendezvous_ que significa _encuentro_ en un punto de ejecución, y ninguno de los dos hilos pueden continuar su ejecución hasta que el otro haya llegado. Nota: Puede crear varias soluciones a este problema.

### Ejercicio: Encuentro de ajedrez

En un torneo de ajedrez los participantes efectúan el siguiente itinerario tradicional. Los jugadores y árbitros se identifican para ingresar al centro deportivo (`enter_room`). Cada jugador ubica la mesa con su tablero y se sienta en ella. Una vez que ambos jugadores están presentes, avisan al árbitro. El árbitro establece el tiempo en el reloj (`set_clock`) del tablero y con ello ambos jugadores inician la partida (`play_chess`). 

El problema se considera resuelto si el árbitro establece el reloj sólo hasta que los dos jugadores hayan ingresado al centro deportivo (`enter_room`) y los jugadores juegan (`play_chess`) hasta que el árbitro haya establecido el reloj (`set_clock`). Considere el siguiente código inicial que trata de representar el escenario descrito.

Agregue control de concurrencia al código inicial para considerando todas las posibles rutas de ejecución, el problema siempre esté resuelto.

## Exclusión mutua con semáforos (_mutex_)

### Asimétrica [sem_mutex_asym]

Agregue semáforos al pseudocódigo siguiente para forzar a que los incrementos en los hilos se hagan con exclusión mutua.

**Nota:** Un semáforo inicializado en 1 y que nunca supera este valor, es un *semáforo binario*. Es equivalente a un mutex excepto que no tiene dueño (_ownership_). Cuando el semáforo tiene el valor 1 indica que el mutex está disponible, y el valor 0 que está bloqueado. Se diferencia en que un mutex nunca supera el valor 1, mientras que un semáforo técnicamente puede hacerlo, y de que un mutex sólo puede ser incrementado por el mismo thread que lo decrementó.

### Simétrica [sem_mutex_sym]

Note que en la actividad anterior ambos threads ejecutaban el código en subrutinas distintas, a lo que se le llama una solución *asimétrica* (separación de asuntos o concurrencia de tareas). Sin embargo, el código de las subrutinas era el mismo y por tanto podría convertirse en una solución _simétrica_. En una solución *simétrica* los hilos ejecutan el mismo código, es decir, la misma subrutina.

Las soluciones simétricas son a menudo más fáciles de generalizar. Agregue semáforos al pseudocódigo siguiente para forzar a que los incrementos hechos por una cantidad arbitraria de hilos sean con exclusión mutua.

## Exclusión mutua acotada (_multiplex_)

Modifique el pseudocódigo dado para que imponga una cota o límite superior de `n` hilos ejecutando una sección de concurrencia acotada. A este patrón se le llama *multiplex* y es útil para problemas donde se tienen distintos entes trabajando al mismo tiempo pero con máximo de capacidad.

Por ejemplo, la cantidad de cajeros atendiendo en las ventanillas de un banco o de clientes patinando en la pista del salón de patines. En este último caso, si la capacidad de la pista se agota, algunos clientes tendrán que esperar afuera, y apenas una persona sale de la pista, otra podrá ingresar de inmediato. Use el código siguiente para reflejar este comportamiento.

## Barrera con semáforos (_barrier_)

### Barrera de una pasada [sem_barrier_1pass]

Generalice su solución a la actividad rendezvous para asegurar que una cantidad arbitraria de hilos no continúen su ejecución hasta que todos hayan alcanzado (ejecutado) el punto de encuentro. Es decir, si se crean `w` hilos, los primeros `w - 1` hilos que lleguen al punto de encuentro deberían esperar hasta que el hilo en la posición `w` llegue al punto de encuentro. En tal momento todos los `w` threads podrán continuar ejecutándose concurrentemente. A este patrón se le conoce como *barrera* (_barrier_). Implemente una barrera con semáforos en el siguiente pseudocódigo para que la instrucción `Statement B` se ejecute sólo hasta que todos los hilos hayan ejecutado la instrucción `Statement A`.

### Barrera reusable con semáforos [sem_barrier_reusable]

Haga que su solución a la actividad de barrera sea reusable. Es decir, que la barrera quede lista para volver a usarse, por ejemplo, dentro de un ciclo. Debe asegurarse de que el contador quede en 0, y los threads que salen de la barrera no se combinen con otros que aún están en ella.

**Sugerencia:** Puede reemplazar la barrera por dos torniquetes. Un *torniquete* (_turnstile_) o "trompo" es un dispositivo de control de acceso que impide o da paso a una secuencia de personas de acuerdo a ciertas condiciones. Se usa típicamente en instalaciones deportivas, transporte público, acceso a edificios, parques de diversiones, y otros.

Un torniquete es un semáforo que detiene a todos los hilos que lleguen a él. Pero apenas un hilo logre pasarlo, inmediatamente habilita el paso al siguiente. Puede pensarse como una manera más elegante de que el último hilo que llega a la barrera haga un ciclo de incrementos por todos los demás.

