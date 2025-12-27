# Lotería de la Abuela

Este proyecto contiene la implementación de una simulación de lotería simple utilizando hilos pThreads.

## Archivos

- `GrandmaLottery.c`: El archivo fuente principal que contiene la lógica de la simulación de la lotería.

## Compilación

Para compilar el programa, use el siguiente comando en la carpeta GrandmaLottery:

```sh
make
```

## Uso

Para ejecutar el programa, use el siguiente comando:

```sh
./bin/GrandmaLottery
```

## Enunciado
Una adorable abuelita juega todos los domingos lotería. Como es peligroso que ella salga de casa, envía a sus dos nietos a comprar un par de pedacitos a vendedores diferentes para incrementar la suerte. Ella siempre juega a "gallo tapado", es decir, sin saber el número que le venden. Sin embargo, cuando sus nietos llegan a la casa, por su cansado estado de la vista ella les tiene que preguntar el número que los vendedores le dieron a cada uno.

Modele la situación anterior, con la abuela como el hilo principal, y los dos nietos como dos hilos secundarios. Los nietos generan un número pseudoaleatorio para representar la compra de la fracción de lotería. La espera de la abuela del regreso a casa de los dos nietos es representado por su join. Los nietos comunican a la abuela los números obtenidos a través del valor de retorno de la rutina secundaria. Indague en la documentación de Pthreads cómo este valor es recuperado por pthread_join(). Implemente dos variantes en que los nietos comunican este valor a la abuela:

    Retornan la dirección de memoria de la variable en la que el hilo secundario tiene el número comprado.

    Retornan el número comprado como una falsa dirección de memoria.

Utilice las herramientas de análisis dinámico de código para determinar cuál de las dos variantes anteriores produce el resultado correcto.

Recuerde revisar que su solución no haga mal uso de la memoria ni la concurrencia, y de apegarse a la covención de estilos. Si usa rand(), el linter advertirá de que este procedimiento no es reentrante. Puede usar el procedimiento rand_r() cuya documentación puede obtener en la línea de comandos con man rand_r.

## Autores

Camila Rodriguez y Jhonny Leung