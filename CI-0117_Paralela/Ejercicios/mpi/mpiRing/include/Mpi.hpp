// Copyright 2024 ECCI-UCR CC-BY-4
#pragma once

#include <mpi.h>
#include <stdexcept>
#include <string>

class Mpi {
  Mpi(const Mpi& other) = delete;
  Mpi(Mpi&& other) = delete;
  Mpi& operator=(const Mpi& other) = delete;
  Mpi& operator=(Mpi&& other) = delete;

 private:
  int processNumber = -1;
  int processCount = -1;
  std::string hostname;

 public:
  Mpi(int& argc, char**& argv) {
    if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
      throw std::runtime_error("could not init MPI");
    }
    if (MPI_Comm_rank(MPI_COMM_WORLD, &this->processNumber) != MPI_SUCCESS) {
      throw std::runtime_error("could not get MPI rank");
    }
    if (MPI_Comm_size(MPI_COMM_WORLD, &this->processCount) != MPI_SUCCESS) {
      throw std::runtime_error("could not get MPI size");
    }
    char processHostname[MPI_MAX_PROCESSOR_NAME] = { '\0' };
    int hostnameLen = -1;
    if (MPI_Get_processor_name(processHostname, &hostnameLen) != MPI_SUCCESS) {
      throw std::runtime_error("could not get processor name");
    }
    this->hostname = processHostname;
  }
  ~Mpi() {
    MPI_Finalize();
  }

 public:
  inline int getProcessNumber() const {
    return processNumber;
  }
  inline int getProcessCount() const {
    return processCount;
  }
  inline std::string getHostname() const {
    return hostname;
  }
  inline int rank() const {
    return this->getProcessNumber();
  }
  inline int size() const {
    return this->getProcessCount();
  }
};
