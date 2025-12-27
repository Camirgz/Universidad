#!/bin/bash

# Directorios
INCLUDE_DIR="../include"
SRC_DIR="../src"
BIN_DIR="../bin"
DB_DIR="../db"

# Archivo ejecutable
EXECUTABLE="ProyectoEjecutable"

# Compilación
g++ -I$INCLUDE_DIR $SRC_DIR/Main.cpp $SRC_DIR/ListaRegistros.cpp $SRC_DIR/ConsultaSQL.cpp -o $BIN_DIR/$EXECUTABLE

# Verificación de la compilación
if [ $? -eq 0 ]; then
    echo "Compilación exitosa. Ejecutable guardado en $BIN_DIR/$EXECUTABLE"
    
    # Ejecutar el programa
    echo "Ejecutando $EXECUTABLE..."
    echo ""
    $BIN_DIR/$EXECUTABLE 
    
else
    echo "Error en la compilación."
fi
