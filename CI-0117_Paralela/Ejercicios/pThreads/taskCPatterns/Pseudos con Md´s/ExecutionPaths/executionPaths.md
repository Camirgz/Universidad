
### Caso 1: Thread A se ejecuta primero completamente
1. `thread_a`: x = 5
2. `thread_a`: print(x) → Salida: "5"
3. `thread_b`: x = 7

**Resultado final:**
- Valor de x: 7
- Salida estándar: "5"

### Caso 2: Thread B se ejecuta primero completamente
1. `thread_b`: x = 7
2. `thread_a`: x = 5
3. `thread_a`: print(x) → Salida: "5"

**Resultado final:**
- Valor de x: 5
- Salida estándar: "5"

### Caso 3: Ejecución intercalada 
1. `thread_a`: x = 5
2. `thread_b`: x = 7
3. `thread_a`: print(x) → Salida: "7"

**Resultado final:**
- Valor de x: 7
- Salida estándar: "7"
