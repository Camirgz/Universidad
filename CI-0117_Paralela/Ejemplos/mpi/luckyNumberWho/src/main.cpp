// Copyright 2024 ECCI-UCR CC-BY-4

#include <unistd.h>
#include <cstdlib>
#include <iostream>

#include "Mpi.hpp"
#include "UniformRandom.hpp"

#define out1 std::cout << "Process " << mpi.rank() << ": "
#define out2 out1 << "my lucky number (" << my_lucky_number << ") "

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
  // MPI_Allreduce(&my_lucky_number, &all_min, /*count*/ 1,
  //     MPI_INT, MPI_MIN, MPI_COMM_WORLD);
  mpi.allReduce(my_lucky_number, all_min, MPI_MIN);
  mpi.allReduce(my_lucky_number, all_max, MPI_MAX);
  mpi.allReduce(my_lucky_number, all_sum, MPI_SUM);

  usleep(mpi.rank() * 50000);

  const double all_average = static_cast<double>(all_sum) / mpi.size();
  // out1 << "all minimum = " << all_min << std::endl;
  // out1 << "all average = " << all_average << std::endl;
  // out1 << "all maximum = " << all_max << std::endl;

  if (my_lucky_number == all_min) {
    out2 << "is the minimum (" << all_min << ")" << std::endl;
  }

  if (my_lucky_number < all_average) {
    out2 << "is less than the average (" << all_average << ")" << std::endl;
  } else if (my_lucky_number > all_average) {
    out2 << "is greater than the average (" << all_average << ")" << std::endl;
  } else {
    out2 << "is equal to the average (" << all_average << ")" << std::endl;
  }

  if (my_lucky_number == all_max) {
    out2 << "is the maximum (" << all_max << ")" << std::endl;
  }
}
