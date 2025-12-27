#!/bin/bash

# Limpiar compilaciones previas
echo "Ejecutando: make clean para limpiar archivos"
make clean

# Compilar con múltiples núcleos
echo "Ejecutando: make -j8"
make -j8

# Generar documentación
echo "Ejecutando: make doc para doxygen"
make doc

# Ejecutar el programa
echo "Ejecutando: make run"
make run
