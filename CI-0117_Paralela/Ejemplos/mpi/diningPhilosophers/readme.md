# Filósofos Comensales

Corrija el siguiente pseudocódigo de concurrencia de recursos compartidos para que resuelva el problema de los filósofos comensales, y por lo tanto, logre cumplir con los **tres requerimientos** clásicos:

1. Evitar el **bloqueo mutuo** (deadlock).
2. Evitar la **inanición** (starvation).
3. Permitir el **máximo de concurrencia** posible.

```pseudo
include::dining_philosophers_laterality.pseudo[]
````

## Recomendaciones para la Corrección

Considere las **condiciones necesarias** para que ocurran problemas de sincronización y cambie **una de ellas a la vez** para explorar soluciones distintas:

1. **Considere la lateralidad de los filósofos**
   Alterne el orden en que los filósofos toman los cubiertos (izquierdo/derecho) para romper la simetría que puede provocar bloqueo mutuo.

2. **Considere la cantidad de filósofos que pueden comer concurrentemente**
   Implemente una política donde solo puedan sentarse a comer `N-1` filósofos al mismo tiempo si hay `N` cubiertos, para evitar un ciclo cerrado de espera.

3. **Haga que los filósofos decidan con variables protegidas por exclusión mutua**
   Use semáforos, mutex o monitores para asegurar que el acceso a los recursos compartidos (cubiertos) esté protegido y sincronizado adecuadamente.

## Objetivo

Modificar el pseudocódigo proporcionado (`dining_philosophers_laterality.pseudo`) para evitar condiciones problemáticas y lograr una solución eficiente, segura y justa al clásico problema de los filósofos comensales.
