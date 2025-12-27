// Copyright 2024 ECCI-UCR CC-BY-4
#include <iostream>
#include "../include/Mpi.hpp"

int main(int argc, char* argv[]) {
  try {
    Mpi mpi(argc, argv);
    const int rank = mpi.getProcessNumber();
    const int count = mpi.getProcessCount();
    const int previous = (count + rank - 1) % count;
    const int next = (rank + 1) % count;

    bool can_print = true;
    if (rank > 0) {
      mpi.receive(can_print, previous);
    }

    std::cout << "Hello from main thread of process " << rank
              << " of " << count << " on " << mpi.getHostname() << std::endl;

    mpi.send(can_print, next);

  } catch (const std::exception& error) {
    std::cerr << "error: " << error.what() << std::endl;
  }
}
