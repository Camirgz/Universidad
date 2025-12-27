CXX = g++
CXXFLAGS = -std=c++11 -pthread -Wall
TARGET = pasteleria

# Directorios
SRCDIR = src
BINDIR = bin

# Archivos fuente y objeto
SRCS = $(SRCDIR)/main.cpp $(SRCDIR)/Platillo.cpp $(SRCDIR)/Pasteleria.cpp $(SRCDIR)/Cocinero.cpp
OBJS = $(BINDIR)/main.o $(BINDIR)/Platillo.o $(BINDIR)/Pasteleria.o $(BINDIR)/Cocinero.o

all: $(BINDIR) $(TARGET)

# Crear directorio bin si no existe
$(BINDIR):
	mkdir -p $(BINDIR)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(BINDIR)/main.o: $(SRCDIR)/main.cpp $(SRCDIR)/Cocinero.h $(SRCDIR)/Pasteleria.h $(SRCDIR)/Platillo.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/main.cpp -o $(BINDIR)/main.o

$(BINDIR)/Platillo.o: $(SRCDIR)/Platillo.cpp $(SRCDIR)/Platillo.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/Platillo.cpp -o $(BINDIR)/Platillo.o

$(BINDIR)/Pasteleria.o: $(SRCDIR)/Pasteleria.cpp $(SRCDIR)/Pasteleria.h $(SRCDIR)/Platillo.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/Pasteleria.cpp -o $(BINDIR)/Pasteleria.o

$(BINDIR)/Cocinero.o: $(SRCDIR)/Cocinero.cpp $(SRCDIR)/Cocinero.h $(SRCDIR)/Platillo.h $(SRCDIR)/Pasteleria.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/Cocinero.cpp -o $(BINDIR)/Cocinero.o

clean:
	rm -rf $(BINDIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)