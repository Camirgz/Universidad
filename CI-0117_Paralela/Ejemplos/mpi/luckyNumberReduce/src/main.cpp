// Copyright 2024 ECCI-UCR CC-BY-4

#include <cstdlib>
#include <iostream>

#include "Mpi.hpp"
#include "UniformRandom.hpp"

#define out1 std::cout << "Process " << mpi.rank() << ": "

void generate_lucky_statistics(Mpi& mpi);

int main(int argc, char* argv[]) {
  try {
    Mpi mpi(argc, argv);
    generate_lucky_statistics(mpi);
  } catch (const Mpi::Error& error) {
    std::cerr << "error: " << error.what() << std::endl;
  }
  return 0;
}

void generate_lucky_statistics(Mpi& mpi) {
  // Generate my lucky number
  const int my_lucky_number = UniformRandom<int>().between(0, 99);
  out1 << "my lucky number is " << my_lucky_number << std::endl;

  int all_min = -1;
  int all_max = -1;
  int all_sum = -1;

  // Update distributed statistics from processes' lucky numbers
  // if (MPI_Reduce(&my_lucky_number, &all_min, /*count*/ 1,
  //     MPI_INT, MPI_MIN, /*root*/ 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
  //   throw Mpi::Error("could not reduce value", mpi);
  // }
  mpi.reduce(my_lucky_number, all_min, MPI_MIN, 0);
  mpi.reduce(my_lucky_number, all_max, MPI_MAX, 0);
  mpi.reduce(my_lucky_number, all_sum, MPI_SUM, 0);

  if (mpi.rank() == 0) {
    const double all_average = static_cast<double>(all_sum) / mpi.size();
    out1 << "all minimum = " << all_min << std::endl;
    out1 << "all average = " << all_average << std::endl;
    out1 << "all maximum = " << all_max << std::endl;
  }
}
