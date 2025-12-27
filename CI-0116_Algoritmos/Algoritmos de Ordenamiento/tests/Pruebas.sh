#!/bin/bash

# Ir a la carpeta source
cd ../source

# Compilar el programa
g++ main.cpp ControladorArrays.cpp Ordenador.cpp -o programa

# Volver a la carpeta tests para guardar las salidas
cd ../tests

# Ejecutar 3 veces y guardar cada salida en un archivo diferente dentro de tests
../source/programa > out1.txt
../source/programa > out2.txt
../source/programa > out3.txt
