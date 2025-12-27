#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/Mpi.hpp"

int main(int argc, char* argv[]) {
  try {
    Mpi mpi(argc, argv);

    const int rank = mpi.rank();
    const int size = mpi.size();

    if (size != 4) {
      if (rank == 0) {
        std::cerr << "Este programa requiere exactamente 4 procesos." << std::endl;
      }
      return 1;
    }

    // Generar número aleatorio entre 0 y 100
    std::srand(static_cast<unsigned>(std::time(0)) + rank);
    int numero_local = std::rand() % 101;

    int suma = numero_local;

    // Comunicación circular (pasa la suma parcial al siguiente)
    for (int i = 0; i < size - 1; ++i) {
      int valor_recibido = 0;
      int from = (rank - 1 + size) % size;
      int to = (rank + 1) % size;

      // Recibir desde el proceso anterior
      mpi.receive(valor_recibido, from);
      suma += valor_recibido;

      // Enviar suma parcial al siguiente proceso
      mpi.send(valor_recibido + numero_local, to);
    }

    std::cout << "Proceso " << rank << " generó " << numero_local
              << ", suma total = " << suma << std::endl;

  } catch (const std::exception& error) {
    std::cerr << "Error: " << error.what() << std::endl;
    return 1;
  }
}
