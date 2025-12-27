# Planificador de Procesos

Este proyecto es una simulación de un planificador de procesos implementado en C++. Permite cargar procesos desde un archivo de texto, organizarlos en una cola, y simular su ejecución utilizando los algoritmos de planificación **Round Robin** y **Por Prioridad**.

## Funcionalidades
- **Carga de procesos** desde un archivo con un formato específico.
- **Simulación de ejecución** con dos algoritmos:
  1. **Round Robin**: Asigna un tiempo fijo (quantum) a cada proceso de manera circular.
  2. **Por Prioridad**: Ejecuta los procesos de acuerdo a su prioridad (0 es la más alta, 10 la más baja).
- Manejo de operaciones de entrada/salida (`e/s`) y simulación de tiempos.

## Requisitos
- Compilador compatible con C++ (por ejemplo, `g++`).
- Sistema operativo Linux (para usar `unistd.h`) o Windows (ajustando a `windows.h` para `Sleep`).

## Estructura del Proyecto
```
PlanificadorDeProcesos/
├── src/
│   ├── Controlador.cpp
│   ├── ListaProcesos.cpp
│   ├── Proceso.cpp
│   ├── Controlador.h
│   ├── ListaProcesos.h
│   ├── Proceso.h
├── build/
│   ├── Controlador.o
│   ├── ListaProcesos.o
│   ├── Proceso.o
├── bin/
│   ├── PlanificadorDeProcesos
├── files/
│   ├── Enunciado.txt
├── README.md
├── Compilaciones.sh
├── Doxyfile
├── LICENSE
├── Enunciado.pdf
└── Makefile
```

## Formato del Archivo de Entrada
Cada archivo de procesos debe seguir este formato:
```
proceso [nombre del proceso] [prioridad del proceso]
instruccion 1
instruccion 2
e/s
e/s
fin proceso
```

### Ejemplo:
```
proceso programa1 0
instruccion 1
instruccion 2
e/s
e/s
instruccion 3
fin proceso

proceso programa2 9
instruccion 4
instruccion 5
e/s
e/s
fin proceso
```

## Uso
### Compilación y ejecución
Usa el siguiente comando para compilar el proyecto:
```bash
make clean ; make ; make run
```

### Interacción
1. El programa solicitará el nombre del archivo de procesos a cargar (ubicado en la carpeta `files/`).
2. Elegir el algoritmo de planificación:
   - `1` para **Prioridad**.
   - `2` para **Round Robin**.
3. El programa simulará la ejecución de los procesos y mostrará los resultados en pantalla.

## Simulación
- **Quantum**: 5 segundos.
- **Tiempo de instrucción normal**: 1 segundo.
- **Tiempo de operación `e/s`**: 3 segundos.

## Notas Importantes
- **Restricciones**: No se utilizaron `list`, `vector`, `map` ni bibliotecas adicionales como `<thread>` o `<chrono>`. El manejo de datos se realiza exclusivamente con listas enlazadas personalizadas.
- El programa fue desarrollado con un enfoque en programación orientada a objetos, con herencia, polimorfismo y temas tratados en el curso.

## Autores
- Camila Rodríguez Águila




- Juan Manuel Alvarado
- Andres Salas Acuña
  
