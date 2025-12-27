## Enunciado

---

Implemente la siguiente simulación. Los hilos de ejecución están celebrando el cumpleaños de uno de ellos y van a romper la piñata. Todos los hilos son muy algorítmicos y todos le pegan con la misma fuerza a la piñata. El usuario confeccionó la piñata y sabe cuántos de estos golpes puede soportar el material, y lo indica como segundo argumento de línea de comandos. El primer argumento es la cantidad de hilos que invitó a la fiesta.

Por más que ha intentado, el usuario no ha logrado educar a los hilos en etiqueta de piñatas. Cuando la piñata hace su aparición, todos los hilos le entran a golpes simultáneamente y se podría pensar que en un instante la rompen y se lanzan a recoger los confites, pero no siempre pasa eso. Raras veces se quedan casi infinitamente dándole palo a la piñata rota. Su simulación debe evitar este extraño y vergonzoso fenómeno.

En su simulación, para mantenerles la emoción, permita que los hilos golpeen la piñata como a ellos le gusta: en cualquier orden. Pero sí imponga la restricción de que sólo un hilo a la vez puede golpearla. La piñata revienta cuando su contador de golpes llega a cero. Cada hilo lleva el conteo de cuántos golpes pudo darle a la piñata. Los hilos reportan en la salida estándar cuántos golpes pudo darle a la piñata y quién logró romperla. El siguiente podría ser un ejemplo hipotético de ejecución.


bin/birthday_pinata 3 10
Thread 2/10: 5 hits, I broke the pinata
Thread 0/10: 1 hits
Thread 1/10: 4 hits

bin
Recuerde como siempre verificar la calidad del código fuente y ejecutable. Su solución no debe producir conduciones de carrera. Es probable que necesite correr el programa con una piñata muy fuerte para ver que varios hilos logren golpearla.


## Descripción

---

Este programa simula una piñata que es golpeada por múltiples hilos en ejecución concurrente. Cada hilo representa a una persona golpeando la piñata y su cantidad de golpes es aleatoria, variando entre 1 y los golpes restantes. Los hilos compiten por romper la piñata, y el primero en agotar los golpes restantes la rompe. Se usa `pthread_mutex` para asegurar acceso seguro a la piñata y evitar condiciones de carrera.