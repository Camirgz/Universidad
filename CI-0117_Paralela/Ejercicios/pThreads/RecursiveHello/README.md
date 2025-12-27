### Enunciado del ejercicio
--- 
Copie su ejemplos/pthreads/hello a ejercicios/pthreads/recursive_hello. Puede renombrar ejercicios/pthreads/recursive_hello/src/hello.c a recursive_hello.c o si lo prefiere, main.c. <br>

Modifique a greet() para recibir un número de tipo size_t. Si este número es 0, greet() imprime una despedida y el número recibido. Luego termina su ejecución. <br>

Si el número que greet() recibe es mayor que cero, imprime un saludo y el número recibido. Luego crea un hilo para que invoque a greet() pero con un número menor que el recibido por parámetro. <br>

Modifique el procedimiento main() para crear una variable local de tipo size_t inicializada en 2. Envíe este número como parámetro de la subrutina greet() que correrá en el hilo secundario. <br>

Recuerde copiar este enunciado en una sección de su documento de análisis ejercicios/pthreads/recursive_hello/readme.md y darle el formato apropiado. En otra sección haga una predicción de la salida de su programa antes de corerlo. Compílelo y córralo con el Makefile. Copie la salida de su programa y péguela en un bloque de código debajo de su predicción. Indique si acertó o no la predicción. <br>

### Ejecución con Makefile
---
Para compilar y ejecutar el programa utilizando el Makefile, siga los siguientes pasos:

1. Abra una terminal y navegue al directorio `Ejercicios/pThreads/RecursiveHello/`.

2. Ejecute el comando `make` para compilar el programa. Esto generará el ejecutable correspondiente.

    ```sh
    make
    ```

3. Una vez que la compilación haya finalizado, ejecute el programa con el siguiente comando:

    ```sh
    ./bin/RecursiveHello 
    ```

Esto ejecutará el programa y mostrará la salida en la terminal.

