# Pseudo - Problema hornos

## Estructura de Datos

```
ESTRUCTURA Platillo:
    id_cocinero
    nombre
    tiempo_horneado
    es_urgente

ESTRUCTURA Pasteleria:
    semaforo hornos_disponibles (valor inicial = 2)
    mutex proteccion_colas
    mutex proteccion_hornos
    cola_urgente
    cola_normal
    horno_ocupado[2]  // array de booleanos
```

---

## Main

```
INICIO
    crear pasteleria con 2 hornos
    
    crear 6 platillos (3 urgentes, 3 normales)
    
    PARA cada platillo:
        crear thread cocinero
        iniciar thread
    
    esperar que todos los threads terminen
    
    limpiar memoria
FIN
```

---

## Thread Cocinero 

```
FUNCIÓN thread_cocinero(mi_platillo):
    
    // 1. Agregar a cola según prioridad
    BLOQUEAR proteccion_colas
        SI mi_platillo.es_urgente:
            agregar a cola_urgente
        SINO:
            agregar a cola_normal
    DESBLOQUEAR proteccion_colas
    
    // 2. Esperar turno para usar horno
    ESPERAR(hornos_disponibles)  // bloquea si no hay hornos libres
    
    // 3. Tomar platillo de la cola
    BLOQUEAR proteccion_colas
        SI cola_urgente no vacía:
            platillo = sacar de cola_urgente
        SINO:
            platillo = sacar de cola_normal
    DESBLOQUEAR proteccion_colas
    
    // 4. Asignar horno específico
    BLOQUEAR proteccion_hornos
        buscar primer horno libre
        marcar horno como ocupado
    DESBLOQUEAR proteccion_hornos
    
    // 5. HORNEAR
    dormir(platillo.tiempo_horneado)
    
    // 6. Liberar horno
    BLOQUEAR proteccion_hornos
        marcar horno como libre
    DESBLOQUEAR proteccion_hornos
    
    // 7. Señalar que hay horno disponible
    SEÑALAR(hornos_disponibles)  // desbloquea un thread en espera
    
FIN FUNCIÓN
```

---

## Mecanismos Claves

### Semáforo (hornos_disponibles)
```
ESPERAR(semaforo):
    SI semaforo > 0:
        semaforo--
        continuar
    SINO:
        BLOQUEAR thread hasta que semaforo > 0

SEÑALAR(semaforo):
    semaforo++
    despertar un thread bloqueado (si existe)
```

### Mutex
```
BLOQUEAR(mutex):
    esperar hasta tener acceso exclusivo
    
DESBLOQUEAR(mutex):
    liberar acceso para otros threads
```

---

## Flujo

```
Thread Cocinero:
│
├──> Agregar platillo a cola (LOCK → agregar → UNLOCK)
│
├──> Esperar horno (semaforo WAIT - puede BLOQUEAR aquí)
│
├──> Sacar platillo de cola (LOCK → sacar → UNLOCK)
│
├──> Asignar horno (LOCK → asignar → UNLOCK)
│
├──> Hornear (sleep)
│
├──> Liberar horno (LOCK → liberar → UNLOCK)
│
└──> Señalar horno disponible (semaforo POST)
```

## Resumen de Sincronización

**Problema**: 6 threads, 2 hornos

**Solución**:
- **Semáforo**: controla cuántos threads usan hornos (max 2)
- **Mutex 1**: protege las colas de platillos
- **Mutex 2**: protege el estado de los hornos

**Resultado**: Ejecución paralela sin conflictos