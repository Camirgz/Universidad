# README

# Búsqueda de Vuelos Baratos

Esta es una aplicación en Java que te permite buscar vuelos directos y económicos entre dos ciudades. La aplicación lee archivos de datos de vuelos en una carpeta seleccionada por el usuario y busca los vuelos que cumplan con ciertos criterios.

## Requisitos

Para utilizar esta aplicación, necesitarás tener instalado [Java](https://www.java.com/) en tu computadora. También necesitarás una carpeta con archivos de datos de vuelos en un formato específico. Los archivos de datos deben tener la siguiente estructura:

```
Precio, CiudadSalida, CiudadLlegada, HoraSalida, HoraLlegada, FechaSalida, FechaLlegada, CodigoVuelo, Asientos

```

Donde:

- `Precio` es el precio del vuelo en dólares (número decimal).
- `CiudadSalida` es la ciudad de salida (código de 3 letras).
- `CiudadLlegada` es la ciudad de llegada (código de 3 letras).
- `HoraSalida` es la hora de salida en formato HH:mm.
- `HoraLlegada` es la hora de llegada en formato HH:mm.
- `FechaSalida` es la fecha de salida en formato DD-MM-YYYY.
- `FechaLlegada` es la fecha de llegada en formato DD-MM-YYYY.
- `CodigoVuelo` es el código del vuelo (dos letras seguidas de cuatro dígitos).
- `Asientos` es la cantidad de asientos disponibles en el vuelo (número entero).

## Uso

1. Ejecuta el programa `Busqueda` en tu entorno Java. Puedes hacerlo desde una terminal utilizando el comando `java Busqueda`.
2. El programa te pedirá que selecciones una carpeta que contenga los archivos de datos de vuelos. Asegúrate de tener estos archivos en un directorio antes de ejecutar el programa.
3. Luego, ingresarás la ciudad de salida y la ciudad de llegada para buscar vuelos directos entre esas ciudades. Las ciudades deben ser ingresadas en formato de tres letras, por ejemplo, "NYC" para Nueva York.
4. El programa buscará en los archivos de la carpeta seleccionada y te mostrará el vuelo más barato que cumpla con los criterios de ciudad de salida, ciudad de llegada , precio más bajo y límite de escalas.

## Criterios de Validez de los Vuelos

Los vuelos que se consideran válidos deben cumplir con los siguientes criterios:

- El precio debe ser un número positivo.
- Las ciudades de salida y llegada deben ser códigos de tres letras diferentes.
- El horario de salida y llegada debe estar en formato HH:mm.
- Las fechas de salida y llegada deben estar en formato DD-MM-YYYY y DD-MM-YYYY respectivamente.
- No se toman en cuenta los vuelos de más de menos de una hora ni de más de 23 horas.
- El código de vuelo debe tener dos letras seguidas de cuatro dígitos.
- La cantidad de asientos debe ser un número positivo.

## Resultados

El programa te mostrará el vuelo más barato encontrado que cumpla con los criterios. Si no se encuentra ningún vuelo que cumpla con los criterios, te mostrará un mensaje de que no se encontraron vuelos disponibles. También se mostrarán los vuelos que no cumplieron con los criterios en caso de que los haya.

## Limitaciones
El programa sólo puede aceptar un total de 50 aerolíneas, cada una con un máximo de 150 vuelos.

## Tecnicismos
Para correr el programa, corra el main de la clase con el mismo nombre. Sin embargo, para que el programa funcione correctamente, debe de tener las siguientes clases en su dispositivo: Interaccion, Busqueda, Aerolinea, Vuelo.

## Miembros

- Camila Rodríguez Águila
    - C36624
- Liqing Yosery Zheng Lu
    - C38680
- Jimena Bejarano Sánchez
    - C31074
