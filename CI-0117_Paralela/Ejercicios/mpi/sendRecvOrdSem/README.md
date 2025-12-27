## Ejercicio: Saludo en Orden con MPI

Modifica el **Ejemplo 44 (hello)** para que los procesos saluden en orden según su identificador (`rank`). Utiliza la comunicación punto a punto con `MPI_Send` y `MPI_Recv` para sincronizar los procesos, simulando semáforos. Recuerda que `MPI_Recv` es una operación bloqueante y puede emplearse para controlar la concurrencia.

La salida debe ser siempre determinística, por ejemplo:

```
Hello from main thread of process 0 of 3 on a_host
Hello from main thread of process 1 of 3 on other_host
Hello from main thread of process 2 of 3 on a_host
```

Cada proceso debe imprimir su saludo en la salida estándar, asegurando el orden mediante la sincronización con comunicación punto a punto.
