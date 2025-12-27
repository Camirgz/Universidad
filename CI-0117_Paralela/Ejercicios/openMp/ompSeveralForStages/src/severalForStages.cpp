// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0
#include <omp.h>
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {

  // Primer argumento: número de hilos
  int thread_count = omp_get_max_threads();
  if (argc >= 2) {
    thread_count = std::atoi(argv[1]);
  }

  // Segundo argumento: número de iteraciones
  int iteration_count = thread_count;
  if (argc >= 3) {
    iteration_count = std::atoi(argv[2]);
  }

  // Tercer argumento: número de etapas
  int stage_count = 3;
  if (argc >= 4) {
    stage_count = std::atoi(argv[3]);
  }

  // Pragma: omp parallel, para iniciar la región paralela
  #pragma omp parallel num_threads(thread_count) default(none) shared(iteration_count, stage_count, std::cout)
  {
    for (int stage = 1; stage <= stage_count; ++stage) { // Itera sobre las etapas
      #pragma omp for
      for (int iteration = 0; iteration < iteration_count; ++iteration) { // Itera sobre las iteraciones0
        #pragma omp critical(stdout) // Para evitar la escritura simultánea en la salida estándar
        std::cout << "stage " << stage << ": " << omp_get_thread_num() << '/'
          << omp_get_num_threads() << ": iteration " << iteration << '/'
          << iteration_count << std::endl;
      }

      #pragma omp single
      {
        #pragma omp critical(stdout)
        std::cout << "stage " << stage << ": " << omp_get_thread_num() << '/'
          << omp_get_num_threads() << ": iteration " << iteration_count << '/'
          << iteration_count << std::endl;
      }

      #pragma omp barrier // Asegura que todos los hilos terminen antes de la siguiente etapa
    }
  }
}
