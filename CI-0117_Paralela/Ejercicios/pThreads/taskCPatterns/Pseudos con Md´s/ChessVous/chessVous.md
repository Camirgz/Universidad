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
 