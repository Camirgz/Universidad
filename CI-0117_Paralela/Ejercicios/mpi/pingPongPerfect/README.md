## Ejercicio: Simulación de Ping-Pong con MPI

Un ejercicio clásico de paso de mensajes es simular un juego de tenis de mesa (ping-pong) entre dos procesos. Uno lanza la bola al otro, quien la recibe y la regresa al primero, y así sucesivamente. Los dos jugadores son incansables y nunca pierden un servicio. 

Su programa debe simular este comportamiento utilizando MPI. Si el programa es invocado con una cantidad distinta de dos jugadores, debe mostrar un mensaje de error y finalizar.

Cada proceso debe imprimir en la salida estándar un mensaje cuando realiza un servicio. Puede permitir que el usuario especifique un segundo argumento de línea de comandos para establecer una espera en milisegundos que tarda un jugador en servir desde que recibe la bola. Esto ayuda a hacer más legible la salida y disminuye el indeterminismo.

### Ejemplo de ejecución

```bash
bin/ping_pong_perfect 2 500
0 serves
1 serves
0 serves
1 serves
^C
```