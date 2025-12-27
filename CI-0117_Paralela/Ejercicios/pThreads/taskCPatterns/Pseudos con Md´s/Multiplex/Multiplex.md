
#### Explicación:
1. **Semáforo contador** (`can_skate`):  
   - Inicializado con `room_capacity` (ejemplo: 10 para una pista con capacidad de 10 patinadores).  
   - Cada `wait()` decrementa el contador (es como si le dieran un "permiso").  
   - Cada `signal()` lo incrementa (libera el permiso).  

2. **Comportamiento**:  
   - Si hay espacio (`can_skate > 0`), los patinadores entran inmediatamente.  
   - Si la pista está llena (`can_skate = 0`), nuevos patinadores esperan hasta que alguien salga (`signal`).  

3. **Garantías**:  
   - Máximo `room_capacity` hilos ejecutando `skate()` concurrentemente.  
   - Ausencia de inanición: Los patinadores entran en orden FIFO (si el semáforo es justo).  
