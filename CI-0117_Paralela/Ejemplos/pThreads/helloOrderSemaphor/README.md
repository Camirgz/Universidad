
# Enunciado

---



Al igual que Ejemplo 5, haga que los threads saluden siempre en orden. Es decir, si se crean w threads, la salida sea siempre en orden


```bash
Hello from thread 0 of w
Hello from thread 1 of w
Hello from thread 2 of w

Hello from thread w of w
```


Utilice una colección de semáforos como mecanismo de sincronización (control de concurrencia).

# Descripción 

Este programa en **C** utiliza **hilos POSIX (pthread) y semáforos** para sincronizar la ejecución de múltiples hilos.  

## **Funcionamiento**  

1. **Inicialización**:  
   - Se determina la cantidad de hilos a crear (por defecto, el número de procesadores disponibles).  
   - Se asigna memoria para los semáforos y la estructura de datos compartida.  
   - Se inicializan los semáforos de manera que solo el primer hilo pueda ejecutarse de inmediato.  

2. **Creación de Hilos**:  
   - Se crean múltiples hilos secundarios.  
   - Cada hilo imprime un mensaje en orden, controlado por semáforos.  

3. **Ejecución de los Hilos** (`greet`):  
   - Cada hilo espera su turno mediante un semáforo.  
   - Una vez que su turno llega, imprime un mensaje.  
   - Luego, libera el semáforo del siguiente hilo en la secuencia.  

4. **Finalización**:  
   - El hilo principal espera a que todos los hilos secundarios terminen.  
   - Se liberan los recursos asignados.  

## **Salida Esperada**  
El programa imprime mensajes en el siguiente orden:  

```plaintext
Hello from main thread  
Hello from secondary thread 0 of N  
Hello from secondary thread 1 of N  
...  
Hello from secondary thread N-1 of N  
```

Donde **N** es el número total de hilos.  

## **Aspectos Técnicos**  
- **Sincronización**: Uso de semáforos para asegurar que los hilos se ejecuten en orden.  
- **Paralelismo**: Implementado con `pthread_create()` y `pthread_join()`.  
- **Manejo de Recursos**: Uso de `malloc()` y `free()` para gestionar memoria dinámicamente.  

---
