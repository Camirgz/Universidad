
### 7. Barrera con semáforos (barrier)

#### 7.1. Barrera de una pasada [sem_barrier_1pass]

**Mecanismo clave**:  
- El **último hilo** (que hace `count = thread_count`) libera `thread_count` señales del semáforo `barrier`.  
- **Problema**: No es reusable (el contador `count` no se reinicia).  

---

#### 7.2. Barrera reusable con torniquete [sem_barrier_reusable]
Solución mejorada con **dos torniquetes** (uno para entrar, otro para salir):


**Cómo funciona**:  
1. **Primer torniquete (`turnstile_in`)**:
   - Inicialmente bloqueado (`0`).  
   - El último hilo lo abre con `signal(turnstile_in)`, liberando a todos.  
2. **Segundo torniquete (`turnstile_out`)**:
   - Inicialmente abierto (`1`).  
   - El último hilo lo cierra para preparar la siguiente ronda.  

**Ventajas**:  
- **Reusabilidad**: El contador `count` se reinicia automáticamente.  
- **Justicia**: Los hilos pasan en orden (FIFO).  
- **Eficiencia**: Evita el "despertar en cascada" del enfoque anterior.  

**Flujo** (con 3 hilos):  
1. Todos ejecutan `Statement A`.  
2. El hilo 3 (último) abre `turnstile_in` → todos pasan a `Statement B`.  
3. El hilo 1 (último en salir) abre `turnstile_out` → prepara la siguiente iteración.  
