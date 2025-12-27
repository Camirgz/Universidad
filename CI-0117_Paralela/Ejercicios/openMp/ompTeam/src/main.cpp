// Copyright 2024 ECCI-UCR CC-BY 4.0

#include <omp.h>       // Librería para programación paralela con OpenMP
#include <iostream>    // Para entrada/salida estándar

// Función que representa una tarea pesada (aún sin implementar)
void heavy_task() {
  // Aquí se podría colocar una operación costosa (ej. cálculo grande)
}

int main(int argc, char* argv[]) {
  // Determina cuántos hilos usar:
  // Si se pasa un argumento, lo convierte a entero y lo usa como número de hilos.
  // Si no, usa la cantidad máxima de hilos disponibles.
  const int thread_count = argc == 2 ? ::atoi(argv[1]) : omp_get_max_threads();

  // Inicia una región paralela con 'thread_count' hilos.
  #pragma omp parallel num_threads(thread_count) \
    default(none) shared(std::cout) firstprivate(thread_count)
  {
    heavy_task(); // Ejecuta la tarea pesada (actualmente vacía)

    // Sección crítica para evitar que varios hilos escriban al mismo tiempo en std::cout
    #pragma omp critical(stdout)
    std::cout << "Hello from secondary thread " << omp_get_thread_num()
              << " of " << thread_count << std::endl;

    // Alternativa (comentada) que también podría usarse:
    // std::cout << " of " << omp_get_num_threads() << std::endl;
  }

  // Mensaje desde el hilo principal
  std::cout << "Hello from main thread" << std::endl;
}

// Código comentado usando hilos POSIX (no se ejecuta gracias a '#if 0')
// Solo se deja como referencia
#if 0
void* rutine(void* data) {
  std::cout << "Hello from secondary thread " << 0
            << " of " << thread_count << std::endl;
}
#endif
