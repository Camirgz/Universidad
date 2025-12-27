## Descripción

Adapte su solución al ejercicio anterior para que sea más realista. El primer argumento de línea de comandos indica el marcador de victoria de la partida. Por ejemplo, si se indica `10`, el primer jugador que anote 10 goles ganará la partida y el juego termina.

En esta versión, los jugadores no son perfectos. El segundo y tercer argumento de línea de comandos indican la probabilidad de acierto en cada servicio (tiro o pase) del primer y segundo jugador, respectivamente.

Por ejemplo, la siguiente ejecución indica que el jugador 1 (proceso 0) tiene una tasa de acierto del 85.5% y el jugador 2 del 88%:

```bash
mpiexec -n 2 ping_pong 3 85.5 88
```

Ejemplo de salida estándar:

```
1: 24 1
2: 53 0
3: 11 0
0 wins 2 to 1
```

En la salida estándar, indique una línea por cada ronda y una línea final con el resultado. En cada ronda se muestra la cantidad de servicios (pases) jugados y el proceso que la ganó. La última línea indica el marcador final o si hubo un empate.

### Argumentos

- `victory_score`: Puntuación necesaria para ganar (ej: 3, 10, 21)
- `hit_rate_p0`: Probabilidad de acierto del jugador 0 (0-100%)
- `hit_rate_p1`: Probabilidad de acierto del jugador 1 (0-100%)