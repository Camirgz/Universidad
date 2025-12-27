# Proyecto Árbol y Lista - C++

Este proyecto contiene implementaciones de estructuras de datos como Árbol Binario de Búsqueda (ArbolB) y Lista, junto con sus respectivas pruebas. Además, se realiza la compilación y ejecución de las pruebas mediante scripts de automatización.

## Estructuras de Datos

- **ArbolB (Árbol Binario de Búsqueda)**: Implementación de un árbol binario de búsqueda que permite insertar, eliminar e imprimir nodos.
- **Lista**: Implementación de una lista enlazada simple que permite agregar elementos.

## Requisitos

- **Sistema operativo**: Linux o Windows (para Windows se requiere el entorno adecuado para compilar con `g++`).
- **Dependencias**:
  - `g++` (GNU Compiler Collection)


## Compilación y Ejecución

Este proyecto incluye un script de automatización para la compilación y ejecución de pruebas. Puedes usar el siguiente comando para compilar todo el proyecto y ejecutar las pruebas:

Para autorizar al archivo
```bash
chmod +x 
```
```bash
./Compilaciones.sh
```

Este script realiza las siguientes acciones:

1. Limpia los archivos anteriores generados (`*.o`).
2. Compila los archivos fuente `.cpp` de las estructuras de datos (`arbol.cpp`, `lista.cpp`).
3. Crea la biblioteca dinámica `libp2ds.so`.
4. Compila y ejecuta los tests definidos en los archivos `arbolTests.cpp` y `listaTests.cpp`.

### Paso 3: Verificar los resultados de las pruebas

Al ejecutar el script, verás en la terminal si las pruebas pasaron o fallaron. El resultado se imprimirá con un color verde si la prueba fue exitosa, o rojo si falló. Ejemplo:

```
arbolTests OK
Caso 1 OK
Caso 2 ERROR
```

### Paso 4: Compilación manual (opcional)

Si prefieres compilar manualmente sin usar el script, puedes seguir estos pasos:

1. **Compilar los archivos de estructuras de datos**:

    ```bash
    g++ -fPIC -I"include" -c src/controller/lista.cpp -o bin/lista.o
    g++ -fPIC -I"include" -c src/controller/arbol.cpp -o bin/arbol.o
    ```

2. **Crear la biblioteca compartida**:

    ```bash
    g++ -shared -o lib/dynamic/libp2ds.so bin/lista.o bin/arbol.o
    ```

3. **Compilar las pruebas**:

    ```bash
    g++ -c tests/tests.cpp -o tests.o
    g++ -I"include" -I"src/controller" -L"lib/dynamic" tests.o tests/arbolTests.cpp -o arbolTests -lp2ds
    ```

4. **Ejecutar las pruebas**:

    ```bash
    ./arbolTests
    ```

## Descripción de las Pruebas

Las pruebas están divididas en dos partes:

1. **Pruebas de `ArbolB`**: Verifica que las operaciones de inserción, eliminación e impresión del árbol binario de búsqueda se realicen correctamente. Estas pruebas están en `arbolTests.cpp`.
   
2. **Pruebas de `Lista`**: Verifica que la operación de agregar elementos a la lista enlazada funcione correctamente. Estas pruebas están en `listaTests.cpp`.

Ambas pruebas usan las funciones `assertEquals` para verificar los resultados esperados con los resultados reales de las operaciones. Si hay un fallo, el nombre de la prueba se imprimirá en rojo, de lo contrario, aparecerá en verde.
