CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pthread -g
TARGET = bin/vm_system

SRC_DIR = ../src
BIN_DIR = bin

SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/cpu.cpp \
          $(SRC_DIR)/memory.cpp \
          $(SRC_DIR)/mmu.cpp \
          $(SRC_DIR)/process.cpp \
          $(SRC_DIR)/tlb_pagetable.cpp \
          $(SRC_DIR)/data_cache.cpp \
          $(SRC_DIR)/virtual_memory_system.cpp

OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SOURCES))

HEADERS = $(SRC_DIR)/virtual_memory_system.h

TEST_DIR = .

all: $(BIN_DIR) $(TARGET)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(TARGET): $(OBJECTS)
	@echo "Enlazando archivos objeto..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Compilacion exitosa: $(TARGET)"

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@echo "Compilando $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Limpiando archivos objeto y ejecutable..."
	rm -rf $(BIN_DIR)
	@echo "Limpieza completada"

run: $(TARGET)
	@echo "Ejecutando con un programa de prueba..."
	$(TARGET) $(TEST_DIR)/program1.txt

run-two: $(TARGET)
	@echo "Ejecutando con 2 procesos (minimo requerido)..."
	$(TARGET) $(TEST_DIR)/program1.txt $(TEST_DIR)/program2.txt

run-multi: $(TARGET)
	@echo "Ejecutando con 4 procesos (maximo)..."
	$(TARGET) $(TEST_DIR)/program1.txt $(TEST_DIR)/program2.txt \
	          $(TEST_DIR)/program3.txt $(TEST_DIR)/program4.txt

run-three: $(TARGET)
	@echo "Ejecutando con 3 procesos..."
	$(TARGET) $(TEST_DIR)/program1.txt $(TEST_DIR)/program2.txt \
	          $(TEST_DIR)/program3.txt

run-lru: $(TARGET)
	@echo "Ejecutando con algoritmo LRU (2 procesos)..."
	$(TARGET) --lru $(TEST_DIR)/program1.txt $(TEST_DIR)/program2.txt

run-lru-multi: $(TARGET)
	@echo "Ejecutando con algoritmo LRU (4 procesos)..."
	$(TARGET) --lru $(TEST_DIR)/program1.txt $(TEST_DIR)/program2.txt \
	          $(TEST_DIR)/program3.txt $(TEST_DIR)/program4.txt

test: $(TARGET)
	@echo "Ejecutando pruebas automatizadas..."
	@echo ""
	@echo "Prueba 1: Un proceso"
	@$(TARGET) $(TEST_DIR)/program1.txt | head -20
	@echo ""
	@echo "Prueba 2: Dos procesos"
	@$(TARGET) $(TEST_DIR)/program1.txt $(TEST_DIR)/program2.txt | head -20
	@echo ""
	@echo "Pruebas completadas"

help:
	@echo "Makefile - Sistema de Memoria Virtual"
	@echo "Camila Rodriguez - Yosery Zheng Lu"
	@echo ""
	@echo "Targets disponibles:"
	@echo ""
	@echo "  make              - Compilar el proyecto"
	@echo "  make clean        - Limpiar archivos compilados"
	@echo "  make run          - Ejecutar con 1 programa"
	@echo "  make run-two      - Ejecutar con 2 programas (minimo)"
	@echo "  make run-three    - Ejecutar con 3 programas"
	@echo "  make run-multi    - Ejecutar con 4 programas (maximo)"
	@echo "  make run-lru      - Ejecutar con 2 programas usando LRU"
	@echo "  make run-lru-multi - Ejecutar con 4 programas usando LRU"
	@echo "  make test         - Ejecutar pruebas automatizadas"
	@echo "  make help         - Mostrar esta ayuda"
	@echo ""

info:
	@echo "Configuracion del Sistema"
	@echo "Compilador: $(CXX)"
	@echo "Flags: $(CXXFLAGS)"
	@echo "Target: $(TARGET)"
	@echo "Directorio de codigo: $(SRC_DIR)"
	@echo "Directorio de binarios: $(BIN_DIR)"
	@echo "Directorio de pruebas: $(TEST_DIR)"
	@echo "Archivos fuente:"
	@for src in $(SOURCES); do echo "  - $$src"; done
	@echo ""

check:
	@echo "Verificando archivos necesarios..."
	@for src in $(SOURCES); do \
		if [ -f "$$src" ]; then \
			echo "$$src"; \
		else \
			echo " $$src no encontrado"; \
		fi \
	done
	@echo ""
	@echo "Verificando programas de prueba..."
	@for prog in program1.txt program2.txt program3.txt program4.txt; do \
		if [ -f "$(TEST_DIR)/$$prog" ]; then \
			echo " $(TEST_DIR)/$$prog"; \
		else \
			echo " $(TEST_DIR)/$$prog no encontrado"; \
		fi \
	done

rebuild: clean all

.PHONY: all clean run run-two run-three run-multi run-lru run-lru-multi test help info check rebuild