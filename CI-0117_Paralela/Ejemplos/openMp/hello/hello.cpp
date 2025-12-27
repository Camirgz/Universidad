#include <iostream>

//g++ -fopemt hello.cpp -o hello -fopenmp

int main() {
  #pragma omp parallel // Implementar sección paralela
  {
    #pragma omp critical // Definir región crítica, es como un mutex, solo un hilo a la vez
    // Sin eso puede que se desordenen los hilos, 
    std::cout << "Hello from secondary thread" << std::endl;
  }
}