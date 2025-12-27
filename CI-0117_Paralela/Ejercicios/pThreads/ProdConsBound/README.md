## Simulación del Productor-Consumidor

Cree una simulación del problema del **productor-consumidor**.  
Su programa recibirá **seis argumentos** en la línea de comandos:

1. **Tamaño del buffer**  
2. **Cantidad de rondas** (veces que se debe llenar y vaciar el buffer)  
3. **Duración mínima (ms)** que el productor tarda en generar un producto  
4. **Duración máxima (ms)** que el productor tarda en generar un producto  
5. **Duración mínima (ms)** que el consumidor tarda en consumir un producto  
6. **Duración máxima (ms)** que el consumidor tarda en consumir un producto  

---

### Funcionamiento

- El programa debe crear un buffer para almacenar productos identificados por números secuenciales, iniciando en `1`.
- Por ejemplo: si se piden `2 rondas` con un `buffer` de tamaño `3`, el producto `4` identificará el primer producto de la segunda ronda.

#### Producción
- Generar un producto no es inmediato.
- El tiempo de producción se determina mediante una duración **pseudoaleatoria** entre los argumentos **3** y **4**.
- Cada vez que el productor genera un producto:
  1. Espera la duración aleatoria.
  2. Agrega el producto al buffer.
  3. Imprime en la salida estándar:

```bash
Produced i
```

> Donde `i` es el número del producto.

#### Consumo
- Una vez que el consumidor extrae un producto del buffer:
  1. Imprime:

```bash
    Consuming i
```

  2. Espera una duración pseudoaleatoria entre los argumentos **5** y **6**.

> **Sugerencia:** Indente la salida del consumidor para distinguirla visualmente de la del productor.

---

### Ejemplo de ejecución

En el siguiente ejemplo:
- Se ejecutan `2 rondas`
- El buffer tiene tamaño `3`
- El productor es rápido (`0-100ms`)
- El consumidor es lento (`0-750ms`)

```bash
$ ./producer_consumer 3 2 0 100 0 750
Produced 1
Produced 2
Produced 3
        Consuming 1
Produced 4
        Consuming 2
Produced 5
        Consuming 3
        Consuming 4
        Consuming 5
Produced 6
        Consuming 6
```

Como se observa:
- El productor llena rápidamente el buffer.
- Luego, espera hasta que el consumidor libere espacio.
- El consumidor procesa todos los productos en el **mismo orden** en que fueron generados.
