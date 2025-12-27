# Enunciado

---

Modifique su solución de Ejemplo 7 para inicializar todos los semáforos en 0. Luego haga que el hilo principal incremente el semáforo del hilo 0. ¿Produce el mismo resultado que su solución anterior?

# ¿Qué pasa si el hilo principal incrementa el semáforo del hilo 0 después de hacer su saludo Hello from main thread?

---

El programa está diseñado para que:
1. El hilo principal cree todos los hilos secundarios.
2. Imprima `"Hello from main thread"`.
3. **Luego** active al primer hilo secundario (`hilo 0`) con `sem_post(&can_greet[0])`.

- El mensaje `"Hello from main thread"` siempre aparece **antes** que cualquier saludo de los hilos secundarios.
- Los hilos secundarios **esperan** en `sem_wait(...)` hasta que se les dé permiso en orden.
