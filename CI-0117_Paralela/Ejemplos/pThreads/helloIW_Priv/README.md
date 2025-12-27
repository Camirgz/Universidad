### Enunciado 
---
Cree una nueva versión de su programa "hola mundo" donde cada thread imprime "Hello from secondary thread i of w", donde i es el número de thread y w la cantidad total de hilos creada. Está prohibido usar variables en el segmento de datos (globales, estáticas, externas). Cree un registro de memoria (estructura) privado para cada thread.

### Descripción del Programa
---
El programa `helloIW.c` crea múltiples hilos (threads) que imprimen un mensaje personalizado. Cada hilo imprime "Hello from secondary thread i of w", donde `i` es el número del hilo y `w` es la cantidad total de hilos creados. El programa no utiliza variables globales, estáticas o externas, y cada hilo tiene su propia **estructura de datos privada**.
