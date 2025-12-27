# Enunciado

Se introducen dos procedimientos al pseudocódigo para crear y esperar por equipos de hilos:

```pseudocode
procedure main():
    shared thread_count := 5
    declare team := create_threads(thread_count, routine)
    ...
    join_threads(team)
end procedure

procedure routine(thread_number)
    print("I am thread ", thread_number, " of ", thread_count)
end procedure
```

El procedimiento `create_threads()` crea un equipo de hilos, todos ejecutando el procedimiento `routine()` concurrentemente, y retorna un arreglo de valores que representan hilos de ejecución. De forma análoga, el procedimiento `join_threads()` recibe el arreglo de hilos y espera a que todos ellos finalicen su ejecución.

Contar con estos dos procedimientos reutilizables es sumamente útil para la implementación de equipos de hilos en el paralelismo de datos. Las siguientes son implementaciones iniciales usando Pthreads:

```c
pthread_t* create_threads(size_t count, void*(*routine)(void*), void* data) {
    pthread_t* threads = (pthread_t*) calloc(count, sizeof(pthread_t));
    if (threads) {
        for (size_t index = 0; index < count; ++index) {
            if (pthread_create(&threads[index], NULL, routine, data) != 0) {
                fprintf(stderr, "error: could not create thread %zu\n", index);
                join_threads(index, threads);
                return NULL;
            }
        }
    }
    return threads;
}

int join_threads(size_t count, pthread_t* threads) {
    int error_count = 0;
    for (size_t index = 0; index < count; ++index) {
        const int error = pthread_join(threads[index], NULL);
        if (error) {
            fprintf(stderr, "error: could not join thread %zu\n", index);
            ++error_count;
        }
    }
    free(threads);
    return error_count;
}
```

Las implementaciones anteriores no proveen a los hilos secundarios su número de hilo en el equipo. Modifique la subrutina `create_threads()` para que cree en la memoria dinámica e inicialice un arreglo de registros de datos privados. Cada registro tiene cuatro valores: el número de hilo (obtenido del índice de un ciclo), la cantidad de hilos en el equipo de hilos, el puntero a los datos compartidos (`data`, recibido por parámetro), y el identificador del hilo (`pthread_t`) inicializado con `pthread_create()`. Envíe la dirección del registro privado a cada hilo al crearlo con `pthread_create()`. Finalmente, `create_threads()` retorna la dirección de este arreglo de registros privados en lugar del arreglo de identificadores de hilos (`pthread_t`).

Modifique a `join_threads()` para que reciba la cantidad de hilos y la dirección al arreglo de registros privados (en lugar del arreglo de identificadores de hilos). Luego esperará por cada hilo con `pthread_join()` usando el identificador del hilo en los datos privados. Finalmente, libera el arreglo de datos privados.

Con estos cambios, los hilos podrán saber su número de hilo (`thread_number`) y la cantidad de hilos que hay en el equipo (`thread_count`) accediendo a los campos del registro privado.

Aplique estas subrutinas a un ejemplo o ejercicio que utilice equipos de hilos, como Ejemplo 2 o Ejercicio 8 [team_shot_put].

## Descripción

Las nuevas funciones implementadas son:

### 1. **`create_threads`**
Esta función crea un equipo de hilos y les asigna una tarea común, ejecutando una rutina (función) específica en cada hilo. Además, crea un registro privado para cada hilo con información sobre su número de hilo, la cantidad de hilos en el equipo, el puntero a los datos compartidos y el identificador del hilo.

- **Parámetros**:
    - `count`: número de hilos a crear.
    - `routine`: función que cada hilo ejecutará.
    - `data`: datos compartidos entre todos los hilos.
- **Retorno**: un arreglo de registros privados, cada uno correspondiente a un hilo.

**Proceso**:
- Reserva memoria para los hilos.
- Crea cada hilo con `pthread_create`, pasando la información del hilo a través del registro privado.
- Si se encuentra un error en la creación de los hilos, se liberan los recursos y se retorna `NULL`.

### 2. **`join_threads`**
Esta función espera que todos los hilos finalicen su ejecución. Recibe un arreglo de registros privados y, para cada hilo, usa `pthread_join` para esperar su terminación. Al final, libera la memoria reservada para los registros privados.

- **Parámetros**:
    - `count`: número de hilos.
    - `threads`: arreglo de registros privados que contiene la información de cada hilo.
- **Retorno**: un contador de errores si ocurre algún problema al esperar por los hilos.

**Proceso**:
- Para cada hilo, espera que termine usando `pthread_join`.
- Si ocurre un error al esperar el hilo, incrementa un contador de errores.
- Finalmente, libera la memoria de los registros privados.

### Objetivo de estas funciones
Estas dos funciones facilitan la gestión de los hilos, permitiendo:

- Crear hilos con datos privados asociados (como el número de hilo y la cantidad de hilos en el equipo).
- Manejar el ciclo de vida de los hilos de forma eficiente, esperando que todos terminen antes de proceder.
- Mejorar la claridad y modularidad del código al separar la creación y espera de hilos en funciones reutilizables.
