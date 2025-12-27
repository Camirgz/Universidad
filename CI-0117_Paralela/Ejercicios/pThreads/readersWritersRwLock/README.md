Implemente una solución al problema de los lectores y escritores usando candados de lectura y escritura de Pthreads. Los escritores escriben en un contador compartido, y los lectores reportan el valor leído. Recuerde que varios lectores pueden trabajar al mismo tiempo mientras que en escritor necesita acceso exclusivo al recurso compartido. Su código no debe producir anomalías de memoria ni concurrencia. Puede usar el siguiente código como punto de partida.

``` shell
make
./bin/readersWritersRwLock < tests/input001.txt 
```