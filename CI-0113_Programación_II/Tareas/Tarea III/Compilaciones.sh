#!/bin/bash

# Limpieza de pantalla
echo "Limpiando pantalla..."
clear

# Eliminación de archivos .o en bin
echo "Eliminando archivos .o antiguos en bin..."
rm bin/*.o

# Compilación de lista.cpp
echo "Compilando lista.cpp..."
g++ -fPIC -I"include" -c src/controller/lista.cpp -o bin/lista.o
if [ $? -ne 0 ]; then
    echo "Error en la compilación de lista.cpp"
    exit 1
fi

# Compilación de arbol.cpp
echo "Compilando arbol.cpp..."
g++ -fPIC -I"include" -c src/controller/arbol.cpp -o bin/arbol.o
if [ $? -ne 0 ]; then
    echo "Error en la compilación de arbol.cpp"
    exit 1
fi

# Creación de la biblioteca dinámica
echo "Creando la biblioteca dinámica libp2ds.so..."
g++ -shared -o lib/dynamic/libp2ds.so bin/lista.o bin/arbol.o
if [ $? -ne 0 ]; then
    echo "Error al crear la biblioteca dinámica libp2ds.so"
    exit 1
fi

# Cambiar al directorio de tests
echo "Entrando en la carpeta tests..."
cd tests || exit

# Compilación de tests.cpp
echo "Compilando tests.cpp..."
g++ -c tests.cpp -o tests.o
if [ $? -ne 0 ]; then
    echo "Error en la compilación de tests.cpp"
    exit 1
fi

# Compilación del archivo arbolTests
echo "Compilando arbolTests..."
g++ -I"../include" -I"../src/controller" -L"../lib/dynamic" tests.o arbolTests.cpp -o arbolTests
if [ $? -ne 0 ]; then
    echo "Error en la compilación de arbolTests"
    exit 1
fi

# Ejecución de arbolTests
echo "Ejecutando arbolTests..."
./arbolTests
if [ $? -ne 0 ]; then
    echo "Error al ejecutar arbolTests"
    exit 1
fi

echo "Proceso completado con éxito."
