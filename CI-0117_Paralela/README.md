### Programación Paralela y Concurrente
---
**Ciclo lectivo:** I Semestre, 2025 <br>
**Estudiante:** Camila Rodríguez Águila <br>
**Carné:** C36624 <br>
**Profesor:** Daniel Alvarado González <br>
### Glosario
---
**Programación serial** <br>
Secuencia de instrucciones, ejecuciones "una tras otra", no se va a ejecutar la tarea 2 hasta que se termine de ejecutar la 1, va en orden y es **secuencial**. No hay nada simultáneo.

**Programación concurrente**<br>
Lo que no es serial, todo lo que no es serial es concurrente, por ejemplo se llevan cursos "al mismo tiempo" pero en un momento específico no lo estoy llevando al mismo tiempo, sino, se van alternando las tareas para poder llegar al objetivo de manera más rápida, también se discutió el ejemplo de los sistemas operativos, los cuáles aparentaban ejecutar procesos "al mismo tiempo" cuando realmente lo que hacían es ir **alternando** de manera rápida para que diera esa impresión.

**Programación paralela**<br>
A diferencia de la programación concurrente en este caso ambas tareas se están ejecutando al mismo tiempo, de manera **simultánea**, por ejemplo, el ir silbando y andando en bicicleta, son dos actividades diferentes que se pueden hacer al mismo tiempo. Se pueden considerar situaciones paralelas pero no concurrentes, pero para efectos del curso, consideramos al paralelismo como forma de concurrencia. 

**Concurrencia de tareas**<br>
Es cuando hay varias tareas ejecutándose en un sistema, pero no necesariamente al mismo tiempo. Los hilos hacen trabajos distintos y se van turnando para avanzar en paralelo. Es como hacer varias cosas en el día, pero no todas a la vez, sino alternando entre ellas.

**Paralelismo de datos**<br>
Dividir los datos en partes más pequeñas y asignar cada una a diferentes hilos para que trabajen en ellas al mismo tiempo. Por ejemplo, varias personas simultáneamente realizando una encuesta de datos personales a diferentes grupos en una clase, esto para acabar más rápido.

**Hilo de ejecución**<br>
Lista de valores que el sistema operativo envía al CPU para qeu este se haga cargo de ejecutar. Es como un trabajador que ejecuta instrucciones dentro del CPU. Un programa puede tener un solo hilo (haciendo una tarea a la vez) o varios hilos (haciendo varias cosas en paralelo).

**Indeterminismo**<br>
Incapacidad de conocer de forma precisa y exacta, el orden de ejecución de los programas (hilos paralelos) en el CPU, ya que es el sistema operativo el que se encarga de administrar esto a través del calendarizador. 

**Memoria privada y compartida**<br>
Privada: Espacio de memoria inaccesible sin permiso del autor o del sistema operativo. Cada hilo tiene su propia memoria privada. <br>
Compartida: Segmento accesible para todos los hilos del programa, se define como un atributo dentro de la memoria privada.

**Espera activa**<br>
Proceso en el que se hace mucho pero a la vez no hace nada, se gasta mucho tiempo del CPU y no hace nada, pasa cuando un ciclo de ejecución hace esperar a un hilo hasta que alguna condición se cumpla.

**Condición de carrera**<br>
Tienen que cumplirse 3 condiciones: 
 - Debe haber concurrencia
 - Debe haber memoria compartida entre las unidades de concurrencia
 - Debe haber escritura en memoria <br>

La condición de carrera es cuando hay varios hilos compitiendo por 


**Control de concurrencia**<br>
Forzar el eliminar alguna de las condicionse para que la condición de carrerra no suceda

**Seguridad condicional**<br>
Permite asegurar que los procesos solo tengan acceso a ciertos recursos bajo condiciones específicas. Ejemplo de carriles en una piscina. Esta técnica ayuda a evitar accesos no autorizados, asegurando que los recursos sean utilizados solo cuando se cumplan los requisitos predeterminados, evitando condiciones de carrera.

**Exclusión mutua**<br>
Conocido como MutEx o candandos
Segmento de código en el que debe haber solo un hilo ejecutándose concurrentemente
No es una espera activa, funciona por colas
Analogía con cuellos de botella en carretera

**Semáforo**<br>
Un semáforo lógico es un tipo de semáforo que solo puede tener dos valores: 0 o 1. Si su valor es 1, el recurso está disponible; si es 0, los hilos deben esperar. Se usa para asegurar que solo un hilo acceda a un recurso a la vez. (Rojo/Verde)

**Barrera**<br>
Es una técnica de sincronización usada para asegurar que varios hilos o procesos alcancen un punto común de ejecución antes de continuar. Ninguno avanza hasta que todos hayan llegado, actuando como un punto de reunión obligatorio.

**Variable de condición**<br>
Permite que los hilos se coordinen mediante señales y esperas, deteniéndose hasta que se cumpla cierta condición. Siempre se utiliza junto con un mutex para asegurar el acceso ordenado a recursos compartidos.

**Candado de lectura y escritura**<br>
Es un mecanismo que mejora el acceso concurrente diferenciando entre lectura y escritura: varios hilos pueden leer a la vez, pero solo uno puede escribir, y nunca simultáneamente con lectores. Esto mejora la eficiencia en situaciones donde la lectura es más frecuente que la escritura.

**Descomposición**<br>
Consiste en dividir un problema en tareas más pequeñas que pueden ejecutarse en paralelo. Se busca que estas tareas sean lo más independientes posible para reducir la necesidad de sincronización. Existen varios enfoques: dividir datos, usar recursividad, explorar diferentes posibilidades o trabajar con predicciones.

**Mapeo**<br>
- Después de descomponer un problema en tareas más pequeñas dentro de la programación paralela o concurrente, el paso siguiente es el mapeo, que consiste en asignar estas tareas a los diferentes ejecutantes, como procesos o hilos. El propósito principal es distribuir eficientemente el trabajo entre los recursos disponibles para optimizar el rendimiento y reducir el tiempo de ejecución total. <br>

- **Mapeo estático**: En este tipo de mapeo, la asignación de tareas se realiza de antemano, antes de que comience la ejecución del programa, y permanece sin cambios durante todo el proceso.

- **Mapeo dinámico**: Aquí, las tareas se distribuyen de manera flexible a lo largo del tiempo de ejecución, lo que permite ajustar la carga de trabajo en tiempo real. De este modo, si algunos ejecutantes finalizan antes que otros, pueden asumir nuevas tareas pendientes.

**Incremento de velocidad (speedup)**<br>
Describe la mejora el rendimiento de un programa cuando se ejecuta utilizando varios procesadores o núcleos, en comparación con su ejecución en un solo procesador. El objetivo es calcular el speedup o aceleración obtenida. Esta mejora depende de varios factores, entre ellos la Ley de Amdahl.

**Eficiencia**<br>
La eficiencia es una métrica que varía entre 0 y 1 y mide qué tan bien se aprovechan los recursos en la ejecución paralela. Un valor de 1.0 representa la eficiencia perfecta, donde todas las tareas se ejecutan en paralelo sin interferencias ni tiempos muertos. No obstante, alcanzar ese valor es muy poco común, ya que la mayoría de los programas incluyen partes secuenciales (por ejemplo, la inicialización de hilos o la gestión de recursos compartidos mediante mecanismos como la exclusión mutua), además de las secciones paralelas.

**Comunicación punto a punto entre procesos**<br>

**Comunicación colectiva entre procesos**<br>

**Reducción**<br>

---

### Índice 

---

[Tareas](https://github.com/Camirgz/Concurrente25A-Camila_Rodriguez/tree/main/Tareas) <br>
  &nbsp;&nbsp;&nbsp;&nbsp;[Serial](https://github.com/Camirgz/Concurrente25A-Camila_Rodriguez/tree/main/Tareas/Serial) <br>
  &nbsp;&nbsp;&nbsp;&nbsp;[pThread](https://github.com/Camirgz/Concurrente25A-Camila_Rodriguez/tree/main/Tareas/pThreads) <br>
  &nbsp;&nbsp;&nbsp;&nbsp;[Optimized](https://github.com/Camirgz/Concurrente25A-Camila_Rodriguez/tree/main/Tareas/Optimized) <br>
[Ejercicios](https://github.com/Camirgz/Concurrente25A-Camila_Rodriguez/tree/main/Ejercicios) <br>
    &nbsp;&nbsp;&nbsp;&nbsp;[pThreads](https://github.com/Camirgz/Concurrente25A-Camila_Rodriguez/tree/main/Ejercicios/pThreads)<br>
    &nbsp;&nbsp;&nbsp;&nbsp;[openMp](https://github.com/Camirgz/Concurrente25A-Camila_Rodriguez/tree/main/Ejercicios/openMp)<br>
    &nbsp;&nbsp;&nbsp;&nbsp;[mpi](https://github.com/Camirgz/Concurrente25A-Camila_Rodriguez/tree/main/Ejercicios/mpi)<br>
[Ejemplos](https://github.com/Camirgz/Concurrente25A-Camila_Rodriguez/tree/main/Ejemplos) <br>
    &nbsp;&nbsp;&nbsp;&nbsp;[pThreads](https://github.com/Camirgz/Concurrente25A-Camila_Rodriguez/tree/main/Ejemplos/pThreads)<br>
    &nbsp;&nbsp;&nbsp;&nbsp;[openMp](https://github.com/Camirgz/Concurrente25A-Camila_Rodriguez/tree/main/Ejemplos/openMp)<br>
    &nbsp;&nbsp;&nbsp;&nbsp;[mpi](https://github.com/Camirgz/Concurrente25A-Camila_Rodriguez/tree/main/Ejemplos/mpi)<br>
[Common](https://github.com/Camirgz/Concurrente25A-Camila_Rodriguez/tree/main/common) <br>

