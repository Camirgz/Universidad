// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0
#include <omp.h>
#include <iostream>

int main(int argc, char* argv[]) {
  int thread_count = omp_get_max_threads();
  if (argc >= 2) {
    thread_count = atoi(argv[1]);
  }

  int iteration_count = thread_count; // Valor por defecto
  if (argc >= 3) { // Si se pasa un segundo argumento, se toma como el número de iteraciones
    iteration_count = atoi(argv[2]);
  }

  #pragma omp parallel for num_threads(thread_count) \
    default(none) shared(iteration_count, std::cout)
  for (int iteration = 0; iteration < iteration_count; ++iteration) { // Iteración
    #pragma omp critical(stdout) // Mutex para la salida estándar
    std::cout << omp_get_thread_num() << '/' << omp_get_num_threads() // Número de hilos
      << ": iteration " << iteration << '/' << iteration_count << std::endl;
  }
}
