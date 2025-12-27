# **Draftosaurus**

---

Este proyecto consiste en un juego de dinosaurios donde dos jugadores compiten por crear zonas con diferentes especies de dinosaurios y ganar puntos. A continuación, se describe cómo funciona el código y cómo se juega.

## **Cómo Jugar**

### **Inicio del Juego**

El juego comienza con una bolsa de dinosaurios que contiene las especies disponibles:

- La T: T-Rex
- La V: Velociraptor
- La A: Allosaurus
- La B: Brachiosaurus
- La D: Diplodocus
- La S: Stegosaurus

### **Selección de Dinosaurios**

Cada jugador selecciona 6 especies de dinosaurios de manera aleatoria de la bolsa. Esto se realiza mediante el método **SeleccionadorDeDinosaurios**.

### **Rondas de Juego**

El juego se juega en rondas. Cada ronda consta de 12 turnos (6 para cada jugador) y en total 2 rondas en las que se mantiene el tablero.

En cada turno, el jugador debe seleccionar un dinosaurio y una zona en la que colocarlo. Las zonas disponibles son:

- Bosque de la Semejanza
- Prado de la Diferencia
- Pradera del Amor
- Trio Frondoso
- Rey de la Selva
- Isla Solitaria
- Río

Se utiliza el método **ConseguidorDeDinosaurio** para obtener el dinosaurio y la zona seleccionados.

Algunas zonas tienen reglas especiales que otorgan puntos adicionales.

### **Puntuación**

Al final del juego, se calcula la puntuación de cada jugador utilizando los métodos **CalculadorDePuntos1** y **CalculadorDePuntos2**.

Las reglas de puntuación se basan en la cantidad y tipo de dinosaurios en las zonas de cada jugador.

### **Ganador**

El jugador con la puntuación más alta al final del juego gana.

## **Ejecución del Código**

Para ejecutar el juego, es necesario compilar y ejecutar el archivo Java que contiene este código. Para correr el juego completo, corra la clase Main, teniendo en posesión las otras dos clases (Run y Metodos).
El código trata de ser resiliente ante entradas inválidas, por lo que le pedirá al usuario que ingrese nuevamente lo requerido si no lo hizo.

## **¡Diviértete jugando!**

*Profesor Mauricio Pandolfi*

- Tarea Programada #1 - Programación I - Universidad de Costa Rica
    - Camila Rodríguez Águila (C36624)
    - Liqing Yosery Zheng Lu (C38680)