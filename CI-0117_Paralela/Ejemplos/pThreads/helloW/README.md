### Enunciado

---
Modifique el programa de "hola mundo" para crear una cantidad arbitraria de hilos de ejecución. Cada uno de los cuales imprime "Hello from secondary thread i" en la salida estándar y termina su ejecución. Permita al usuario indicar la cantidad de hilos de ejecución como argumento de la línea de comandos. Si este argumento se omite, suponga la cantidad de CPUs disponibles en el sistema.

### Var Thread Count

---

``` c
uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);
```

sysconf(_SC_NPROCESSORS_ONLN) <br>

- Obtiene el número de procesadores disponibles en el sistema.
Inicialmente, thread_count se establece con ese valor.

``` c
if (argc == 2)
```

Se verifica si el usuario proporcionó exactamente un argumento además del nombre del programa (por eso argc == 2).

``` c
sscanf(argv[1], "%" SCNu64, &thread_count) == 1
```

- argv[1] es el argumento proporcionado por el usuario.

- sscanf() intenta convertir argv[1] a un número de tipo uint64_t y guardarlo en thread_count.

- "%" SCNu64 es la especificación de formato correcta para leer un uint64_t en C.

- Si la conversión tiene éxito (sscanf() devuelve 1), thread_count se actualiza con el valor ingresado.

Si el usuario ingresó un valor inválido

- sscanf() devuelve un número distinto de 1.
- Se imprime un mensaje de error: "Error: invalid thread count"
- Se retorna 11, lo que indica que el programa terminó con un error.
