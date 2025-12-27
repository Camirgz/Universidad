BIN_DIR = bin
SRC_DIR = source
TEST_DIR = tests
EXEC = $(BIN_DIR)/programa
SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/Controlador.cpp

all: $(EXEC)

$(EXEC): $(SRC)
	mkdir -p $(BIN_DIR)
	g++ $(SRC) -o $(EXEC)

exe: all
	$(EXEC)

clean:
	rm -rf $(EXEC)

tests: all
	mkdir -p $(TEST_DIR)
	$(EXEC) > $(TEST_DIR)/out1.txt
	$(EXEC) > $(TEST_DIR)/out2.txt
	$(EXEC) > $(TEST_DIR)/out3.txt
	@echo "Pruebas guardadas en $(TEST_DIR)/out1.txt, out2.txt y out3.txt"
