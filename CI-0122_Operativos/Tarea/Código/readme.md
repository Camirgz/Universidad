# SOLUCIÓN: HORNO COMPARTIDO
## Problema de Sincronización - Pastelería Francesa

### Descripción del Problema
En una reconocida pastelería francesa se tienen dos hornos en una cocina que debe ser compartida entre varios cocineros. Cada cocinero quiere hornear pasteles, postres o bocadillos que toman tiempo variable. Si los hornos están ocupados, los cocineros deben esperar. Además, algunos platillos son urgentes y deben saltarse la fila.

---

## Arquitectura de la Solución

### Clases Implementadas

#### 1. **Platillo** (Platillo.h / Platillo.cpp)
Representa un platillo a hornear con sus características:
- `id_cocinero`: Identificador del cocinero que lo prepara
- `nombre_platillo`: Nombre descriptivo del platillo
- `tiempo_horneado`: Tiempo que tarda en hornearse (en segundos)
- `urgente`: Indica si tiene prioridad o no

#### 2. **Pasteleria** (Pasteleria.h / Pasteleria.cpp)
Gestiona los recursos compartidos (los 2 hornos) y la sincronización:

**Recursos de Sincronización:**
- `sem_t hornos_disponibles`: Semáforo contador inicializado en 2 (cantidad de hornos)
- `pthread_mutex_t mutex_colas`: Protege el acceso a las colas de espera
- `pthread_mutex_t mutex_hornos`: Protege la asignación/liberación de hornos
- `pthread_mutex_t mutex_cout`: Sincroniza la salida a consola

**Estructuras de Datos:**
- `queue<Platillo> cola_urgente`: Cola de alta prioridad
- `queue<Platillo> cola_normal`: Cola de prioridad normal
- `bool horno_ocupado[2]`: Estado de cada horno

**Métodos Principales:**
- `agregar_a_cola()`: Agrega un platillo a la cola correspondiente según prioridad
- `hornear_platillo()`: Proceso completo de espera, asignación, horneado y liberación

#### 3. **Cocinero** (Cocinero.h / Cocinero.cpp)
Representa un thread que ejecuta el proceso de un cocinero:
- Cada cocinero es un pthread independiente
- Agrega su platillo a la cola
- Invoca el proceso de horneado

---

## Mecanismos de Sincronización Utilizados

### 1. **Semáforo Contador (hornos_disponibles)**
```cpp
sem_t hornos_disponibles;  // Inicializado en 2
```
- **Propósito**: Controlar el acceso a los 2 hornos disponibles
- **Operaciones**:
  - `sem_wait()`: Decrementar cuando un cocinero toma un horno
  - `sem_post()`: Incrementar cuando un cocinero libera un horno
- **Garantía**: Máximo 2 cocineros horneando simultáneamente

### 2. **Mutex para Colas (mutex_colas)**
```cpp
pthread_mutex_t mutex_colas;
```
- **Propósito**: Exclusión mutua al acceder/modificar las colas
- **Protege**: 
  - Agregar platillos a las colas
  - Extraer el siguiente platillo según prioridad
  - Verificar si hay platillos esperando

### 3. **Mutex para Hornos (mutex_hornos)**
```cpp
pthread_mutex_t mutex_hornos;
```
- **Propósito**: Exclusión mutua al asignar/liberar hornos específicos
- **Protege**:
  - Búsqueda de horno disponible
  - Marcado de horno como ocupado
  - Marcado de horno como libre

### 4. **Sistema de Prioridades**
```cpp
if (!cola_urgente.empty()) {
    platillo = cola_urgente.front();
    cola_urgente.pop();
} else {
    platillo = cola_normal.front();
    cola_normal.pop();
}
```
- Los platillos urgentes se procesan primero
- Se utiliza una cola separada para cada nivel de prioridad

---

## Flujo de Ejecución

### Proceso de un Cocinero

1. **Agregar a Cola** (Sección Crítica)
   ```
   mutex_colas.lock()
   if (urgente)
       cola_urgente.push(platillo)
   else
       cola_normal.push(platillo)
   mutex_colas.unlock()
   ```

2. **Esperar Horno Disponible**
   ```
   sem_wait(hornos_disponibles)  // Bloquea si no hay hornos libres
   ```

3. **Obtener Platillo con Prioridad** (Sección Crítica)
   ```
   mutex_colas.lock()
   platillo = obtener_siguiente_platillo()  // Prioriza urgentes
   mutex_colas.unlock()
   ```

4. **Asignar Horno Específico** (Sección Crítica)
   ```
   mutex_hornos.lock()
   num_horno = asignar_horno()  // Busca horno libre (0 o 1)
   mutex_hornos.unlock()
   ```

5. **Hornear** (Uso del Recurso)
   ```
   sleep(tiempo_horneado)  // Simula el horneado
   ```

6. **Liberar Horno** (Sección Crítica)
   ```
   mutex_hornos.lock()
   liberar_horno(num_horno)
   mutex_hornos.unlock()
   ```

7. **Señalizar Disponibilidad**
   ```
   sem_post(hornos_disponibles)  // Incrementa hornos disponibles
   ```

---

## Propiedades Garantizadas

### 1. **Exclusión Mutua**
- Solo un thread a la vez puede modificar las colas (protegido por `mutex_colas`)
- Solo un thread a la vez puede asignar/liberar hornos (protegido por `mutex_hornos`)

### 2. **Sincronización**
- Máximo 2 cocineros horneando simultáneamente (controlado por semáforo)
- Los cocineros esperan si ambos hornos están ocupados

### 3. **Prioridad**
- Los platillos urgentes siempre se procesan antes que los normales
- Se respeta el orden FIFO dentro de cada nivel de prioridad

### 4. **Ausencia de Deadlock**
- Los mutex se adquieren siempre en el mismo orden
- Se liberan correctamente después de cada uso
- No hay espera circular

### 5. **Ausencia de Starvation**
- Aunque los urgentes tienen prioridad, eventualmente todos los platillos se hornean
- El semáforo garantiza progreso cuando hay hornos disponibles

---

## Compilación y Ejecución

### Compilar:
```bash
make
```

### Ejecutar:
```bash
./pasteleria
```

### Limpiar archivos objeto:
```bash
make clean
```



