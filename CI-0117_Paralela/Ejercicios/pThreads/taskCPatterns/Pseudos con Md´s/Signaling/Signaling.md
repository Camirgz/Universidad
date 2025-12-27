
#### 3.1. Solución para 2 hilos (a1 < b1)

- Semáforo `a1_ready` inicializado en 0 (bloqueado)
- `thread_a` ejecuta `a1` y luego libera el semáforo con `signal(a1_ready)`
- `thread_b` espera con `wait(a1_ready)` antes de ejecutar `b1`
`a1` siempre se ejecuta antes que `b1`.

---

#### 3.2. Solución para 3 hilos (a1 < b1 < c1)

1. `thread_a` ejecuta `a1` y señala `a1_ready`.
2. `thread_b` espera `a1_ready`, ejecuta `b1`, y señala `b1_ready`.
3. `thread_c` espera `b1_ready` antes de ejecutar `c1`.  
`a1 → b1 → c1`.

---

#### 3.3. Solución general para *w* hilos (a0 < a1 < ... < aw)

1. **Inicialización:**  
   - Semáforo `can_do_a[0]` se inicializa en 1 (para permitir que el primer hilo comience).
   - Los demás semáforos en el arreglo `can_do_a` se inicializan en 0 (bloqueados).

2. **Funcionamiento:**  
   - Cada hilo `i` espera su turno con `wait(can_do_a[i])`.
   - Tras ejecutar `statement a`, libera el semáforo del siguiente hilo con `signal(can_do_a[(i+1) % thread_count])`.

### Ejemplo anterior donde se usó este patrón:  
ChessVouz?