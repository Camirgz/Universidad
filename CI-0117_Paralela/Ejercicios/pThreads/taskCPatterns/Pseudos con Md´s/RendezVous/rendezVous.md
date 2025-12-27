
#### Explicación detallada:
1. **Semáforos inicializados en 0**:
   - `a1_ready`: Señalizado cuando `thread_a` completa `a1`.
   - `b1_ready`: Señalizado cuando `thread_b` completa `b1`.

2. **Flujo de ejecución**:
   - **Caso 1**: Si `thread_a` llega primero al rendezvous:
     - Ejecuta `a1` y señala `a1_ready`.
     - Se bloquea en `wait(b1_ready)` hasta que `thread_b` complete `b1` y señale `b1_ready`.
   - **Caso 2**: Si `thread_b` llega primero:
     - Ejecuta `b1` y señala `b1_ready`.
     - Se bloquea en `wait(a1_ready)` hasta que `thread_a` complete `a1`.

3. **Fijo:**:
   - **Ningún hilo avanza a `a2`/`b2`** sin que el otro haya completado su primera instrucción (`a1`/`b1`).
   - **Ausencia de deadlock**: Siempre hay señalización mutua.
