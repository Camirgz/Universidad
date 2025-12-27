# Makefile modificado para guardar el ejecutable en bin

# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -I./source

# Nombre del ejecutable
TARGET = sintiempo

# Directorios
SRC_DIR = source
BIN_DIR = bin

# Archivos fuente
SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/Grafo.cpp $(SRC_DIR)/FileReader.cpp \
          $(SRC_DIR)/AnalizadorGrafo.cpp $(SRC_DIR)/InterfazUsuario.cpp

# Archivos objeto (en directorio bin)
OBJECTS = $(addprefix $(BIN_DIR)/,$(notdir $(SOURCES:.cpp=.o)))

# Archivos de cabecera
HEADERS = $(SRC_DIR)/Grafo.h $(SRC_DIR)/FileReader.h \
          $(SRC_DIR)/AnalizadorGrafo.h $(SRC_DIR)/InterfazUsuario.h

# Crear directorio bin si no existe
$(shell mkdir -p $(BIN_DIR))

# Regla principal
all: $(BIN_DIR)/$(TARGET)

# Compilar el ejecutable en el directorio bin
$(BIN_DIR)/$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

# Compilar archivos objeto en el directorio bin
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -rf $(BIN_DIR)

# Instalar (opcional)
install: $(BIN_DIR)/$(TARGET)
	cp $(BIN_DIR)/$(TARGET) /usr/local/bin/

# Desinstalar (opcional)
uninstall:
	rm -f /usr/local/bin/$(TARGET)

# Ejecutar con archivo de prueba pequeño
test-small: $(BIN_DIR)/$(TARGET)
	$(BIN_DIR)/$(TARGET) input_small.csv

# Ejecutar con archivo de prueba mediano
test-medium: $(BIN_DIR)/$(TARGET)
	$(BIN_DIR)/$(TARGET) input_medium.csv

# Ejecutar con archivo de prueba grande
test-large: $(BIN_DIR)/$(TARGET)
	$(BIN_DIR)/$(TARGET) input_large.csv

# Generar documentación con Doxygen (opcional)
docs:
	doxygen Doxyfile

# Verificar que no haya memory leaks (requiere valgrind)
memcheck: $(BIN_DIR)/$(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all $(BIN_DIR)/$(TARGET) input_small.csv

# Ayuda
help:
	@echo "Uso del Makefile:"
	@echo "  make          - Compilar el programa (se guarda en bin/)"
	@echo "  make clean    - Limpiar archivos generados"
	@echo "  make test-*   - Ejecutar pruebas con diferentes archivos"
	@echo "  make docs     - Generar documentación"
	@echo "  make memcheck - Verificar memory leaks"
	@echo "  make help     - Mostrar esta ayuda"

.PHONY: all clean install uninstall test-small test-medium test-large docs memcheck help
