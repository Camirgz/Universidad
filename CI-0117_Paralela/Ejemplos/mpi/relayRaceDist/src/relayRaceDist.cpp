// Copyright 2024 ECCI-UCR CC-BY-4

#include <unistd.h>
#include <iostream>

#include "Mpi.hpp"

void relay_race(Mpi& mpi, const int stage1_delay, const int stage2_delay);
void run_stage1(Mpi& mpi, int stage1_delay);
void run_stage2(Mpi& mpi, int stage2_delay);
void referee(Mpi& mpi);

int main(int argc, char* argv[]) {
  try {
    Mpi mpi(argc, argv);
    if (mpi.size() >= 3 && mpi.size() % 2 == 1 && argc == 3) {
      relay_race(mpi, atoi(argv[1]), atoi(argv[2]));
    } else if (mpi.rank() == 0) {
      std::cerr << "usage: mpiexec -np n relay_race stage1_msec stage2_msec\n"
        << "n must be odd and greater or equals to 3\n";
    }
  } catch (const Mpi::Error& error) {
    std::cerr << "error: " << error.what() << std::endl;
  }
  return 0;
}

void relay_race(Mpi& mpi, const int stage1_delay, const int stage2_delay) {
  mpi.barrier();
  if (mpi.rank() == 0) {
    referee(mpi);
  } else if (mpi.rank() % 2 == 1) {
    run_stage1(mpi, stage1_delay);
  } else {
    run_stage2(mpi, stage2_delay);
  }
}

void run_stage1(Mpi& mpi, int stage1_delay) {
  usleep(1000 * stage1_delay);
  const bool baton = true;
  mpi.send(baton, mpi.rank() + 1);
}

void run_stage2(Mpi& mpi, int stage2_delay) {
  bool baton = false;
  mpi.receive(baton, mpi.rank() - 1);
  usleep(1000 * stage2_delay);
  const int team = mpi.rank() / 2;
  mpi.send(team, 0);
}

void referee(Mpi& mpi) {
  const double start = mpi.wtime();
  const int teams = (mpi.size() - 1) / 2;
  for (int place = 1; place <= teams; ++place) {
    int team = -1;
    mpi.receive(team, MPI_ANY_SOURCE);
    const double elapsed = mpi.wtime() - start;
    std::cout << "Place " << place << ": team " << team << " in "
        << elapsed << "s" << std::endl;
  }
}