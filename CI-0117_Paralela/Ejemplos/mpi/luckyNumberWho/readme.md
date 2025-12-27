# Difusión de Reducciones

Modifique su programa `lucky_number_reduce` para que **cada proceso** escoja al azar su número de la suerte entre `00` y `99` inclusive, y el **mismo proceso** reporte si su número es el **menor**, el **mayor**, o cómo se compara con el **promedio** de los números escogidos por todos los procesos.

## Ejemplo de ejecución

```bash
$ mpiexec -np 5 bin/lucky_number_who
Process 0: my lucky number (83) is greater than the average (36.00)
Process 0: my lucky number (83) is the maximum (83)
Process 1: my lucky number (18) is less than the average (36.00)
Process 2: my lucky number (07) is less than the average (36.00)
Process 2: my lucky number (07) is the minimum (07)
Process 3: my lucky number (46) is greater than the average (36.00)
Process 4: my lucky number (26) is less than the average (36.00)
```

### Notas
- El reporte mínimo, máximo y promedio es independiente
- Por ejemplo, si sólo un proceso se ejecuta, cumplirá con los 3 criterios

```bash
$ mpiexec -np 1 bin/lucky_number_who
Process 0: my lucky number (31) is the minimum (31)
Process 0: my lucky number (31) is equals to the average (31.00)
Process 0: my lucky number (31) is the maximum (31)
```