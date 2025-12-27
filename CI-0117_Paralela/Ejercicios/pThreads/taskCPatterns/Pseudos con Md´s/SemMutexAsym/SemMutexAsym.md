#### 5.1. Solución Asimétrica

- El semáforo `can_access_count` actúa como **mutex** (inicializado en 1).  
- Solo un thread puede estar en la sección crítica (incrementando `count`) en cualquier momento.  

#### 5.2. Solución Simétrica (Generalizada para *N* hilos)

**Ventajas**:  
1. **Reutilizable**: El mismo código (`secondary`) se ejecuta en todos los hilos.  
2. **Escalable**: Funciona para cualquier número de hilos (`thread_count`).  
3. **Mantenible**: Cambios en la lógica de exclusión se aplican a todos los hilos.  

