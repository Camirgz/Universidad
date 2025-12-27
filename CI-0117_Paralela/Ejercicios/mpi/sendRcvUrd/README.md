La comunicación punto a punto en MPI es indeterminística entre procesos distintos, pero no entre los mismos procesos. Por ejemplo, si varios procesos envían mensajes a un receptor, los mensajes llegarán en cualquier orden. Pero si un proceso A envía varios mensajes a otro proceso B, los mensajes llegarán en el mismo orden en que fueron enviados.

Modifique la solución de la Ejemplo 48 (send_recv_ord_itm) para que usando comunicación punto a punto, los procesos saluden al proceso intermediario y éste reporte los saludos en el orden en que los recibió.

### Ejecución

en `bin` 

``` bash
mpirun -np 4 sendRcvUrd
```