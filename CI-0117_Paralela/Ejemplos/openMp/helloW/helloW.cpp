// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0
#include <omp.h> //Conjunto de funciones para OpenMP, no siempre es necesario
#include <iostream>

int main(int argc, char* argv[]) {
  int thread_count = omp_get_max_threads(); // Número máximo de hilos
  if (argc == 2) { // Si se pasa un argumento, se toma como el número de hilos
    thread_count = atoi(argv[1]);
  }

  #pragma omp parallel num_threads(thread_count) //numThreads = thread_count
  {
    #pragma omp critical(stdout) // Mutex para la salida estándar
    // Sección crítica, solo un hilo a la vez
    std::cout << "Hello from secondary thread " << omp_get_thread_num()
      << " of " << omp_get_num_threads() << std::endl;
  }
}