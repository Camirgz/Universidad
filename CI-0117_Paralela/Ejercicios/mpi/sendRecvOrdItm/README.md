## Ejercicio: Saludos en Orden con Intermediario

Modifique la solución del **Ejemplo 47 (send_recv_ord_sem)** para que los procesos saluden en orden según su identificador (**rank**) utilizando un proceso intermediario. Es decir, cada proceso enviará su saludo a un miembro designado del equipo, quien recibirá todos los saludos y los imprimirá en la salida estándar en el orden correcto.

Al emplear un intermediario con comunicación punto a punto, se simula una "seguridad condicional". Tenga en cuenta que los saludos deben ser tratados como información vectorial, no escalar. Recuerde que no es posible enviar datos discontinuos de la memoria a través de la red en una sola operación de `send/receive`.