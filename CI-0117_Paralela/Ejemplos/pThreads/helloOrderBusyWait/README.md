### Enunciado
---


Haga que los threads saluden siempre en orden. Es decir, si se crean w threads, la salida sea siempre en orden

Hello from thread 0 of w
Hello from thread 1 of w
Hello from thread 2 of w
...
Hello from thread w of w

Utilice espera activa como mecanismo de sincronización (control de concurrencia).

Ejecute varias veces su solución de hello_order_busywait con la cantidad máxima de threads que el su sistema operativo le permite. ¿Es consistente la duración de su solución con espera activa?

Describa el comportamiento del programa y explique la razón de este comportamiento en el archivo readme.md dentro de su carpeta hello_order_busywait. Indique en qué condiciones sería apremiante utilizar espera activa, o en caso de no haberlas, sugiera soluciones alternativas.

La espera activa (busy waiting) es un ciclo que hace a un hilo de ejecución esperar repetitivamente hasta que una condición se haga falsa. Por ejemplo, si la variable next_thread indica el número del próximo thread que puede realizar una tarea que debe ser serializada en orden, el código

// Wait until it is my turn
while (next_thread < my_thread_id) {
  // busy-wait
}

// Do the ordered-task here
task();

// Allow subsequent thread to do the task
++next_thread;

### Comportamiento del programa

---

### Razón del comportamiento

---