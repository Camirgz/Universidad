
# Enunciado

---

Suponga usted va a construir el edificio para su organización. Para que quede lo mejor posible, usted sólo va a contratar una persona especializada para cada tarea del proceso de construcción. Estas tareas están expresadas en el siguiente grafo de tareas.


![Grafo de tareas](Grafo.PNG)


building tasks
Figura 4. Grafo de tareas de la construcción de un edificio
En un grafo de tareas (task graph) los nodos son tareas de un proceso a realizar, y los vértices son dependencias. Un vértice dirigido de A hacia B indica que la tarea A debe completarse para poder iniciar la tarea B, dado que la salida o productos generados por la tarea A son requeridos por la tarea B. Una tarea puede iniciarse sólo si todas sus dependencias han sido completadas. Dos o más tareas en esta condición pueden realizarse en paralelo.

Se modeló esta situación en un programa concurrente. El maestro de obras (foreman) es el hilo principal que contrató a cada albañil experto. Cada albañil (builder) reporta en la salida estándar cuando inicia su labor. Luego representa el tiempo dedicado con una espera aleatoria. Una vez que finalizada su labor, lo reporta en la salida estándar.

Sin embargo hay un problema con el programa. Una vez que es ejecutado, todos los albañiles inician sus tareas de inmediato, sin respetar las dependencias del grafo de tareas. Por ejemplo, el experto en pintura exterior comienza a pintar las paredes que aún no se han construido. Por favor, corrija esta irrealista situación para que la simulación logre construir el edificio acorde a las dependencias. El programa será correcto cuando no haya forma de que un albañil inicie su actividad antes de que todas sus dependencias hayan sido completadas.

# Descripción y ejecución

---

Este proyecto simula la construcción de una casa utilizando **programación concurrente en C** con **hilos (threads)** y **semáforos** para coordinar el orden de las tareas.

Cada tarea representa una fase del proceso constructivo y depende de otras para poder iniciar. Por ejemplo, no se puede pintar hasta que se hayan construido las paredes.

### Tareas simuladas
1. Construcción de paredes (Obra gris)
2. Plomería exterior
3. Techo
4. Pintura exterior
5. Plomería interior
6. Instalación eléctrica
7. Acabados exteriores
8. Pintura interior
9. Pisos
10. Acabados interiores

Cada una se ejecuta como un hilo independiente, y se sincronizan con semáforos para respetar las dependencias.

---

## Ejecución
Ubicándose en la carpeta ```Ejercicios/pThreads/BuilidingTasks```

``` bash
make
./bin/BuildingTasks <secs>
```