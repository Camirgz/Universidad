#!/bin/bash

echo "Sistema de Memoria Virtual - Pruebas Completas"
echo "Camila Rodriguez - Yosery Zheng Lu"
echo ""

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

if [ ! -f "Makefile" ]; then
    echo -e "${RED}Error: No se encontro Makefile${NC}"
    echo "Asegurate de estar en el directorio tests/"
    exit 1
fi

for prog in program1.txt program2.txt program3.txt program4.txt; do
    if [ ! -f "$prog" ]; then
        echo -e "${YELLOW}Advertencia: No se encontro $prog${NC}"
    fi
done

echo ""
echo "Limpiando compilaciones anteriores..."
make clean > /dev/null 2>&1

echo ""
echo "Compilando el proyecto..."
make
if [ $? -ne 0 ]; then
    echo -e "${RED}Error: Fallo la compilacion${NC}"
    exit 1
fi
echo -e "${GREEN}Compilacion exitosa${NC}"

echo ""
echo "INICIANDO PRUEBAS"
echo ""

echo ""
echo -e "${YELLOW}PRUEBA 1: Proceso Individual${NC}"
echo ""
./bin/vm_system program1.txt
echo ""

echo ""
echo -e "${YELLOW}PRUEBA 2: Dos Procesos (Minimo Requerido)${NC}"
echo ""
./bin/vm_system program1.txt program2.txt
echo ""

echo ""
echo -e "${YELLOW}PRUEBA 3: Tres Procesos${NC}"
echo ""
./bin/vm_system program1.txt program2.txt program3.txt
echo ""

echo ""
echo -e "${YELLOW}PRUEBA 4: Cuatro Procesos (Maximo)${NC}"
echo ""
./bin/vm_system program1.txt program2.txt program3.txt program4.txt
echo ""

echo ""
echo "TODAS LAS PRUEBAS COMPLETADAS"
echo ""
echo -e "${GREEN}Se ejecutaron 4 pruebas diferentes${NC}"
echo ""