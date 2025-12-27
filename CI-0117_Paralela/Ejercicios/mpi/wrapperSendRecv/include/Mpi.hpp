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

  // Métodos map para asociar tipos C++ con tipos MPI
  static inline MPI_Datatype map(bool) { return MPI_C_BOOL; }
  static inline MPI_Datatype map(char) { return MPI_CHAR; }
  static inline MPI_Datatype map(unsigned char) { return MPI_UNSIGNED_CHAR; }
  static inline MPI_Datatype map(short) { return MPI_SHORT; }
  static inline MPI_Datatype map(unsigned short) { return MPI_UNSIGNED_SHORT; }
  static inline MPI_Datatype map(int) { return MPI_INT; }
  static inline MPI_Datatype map(unsigned) { return MPI_UNSIGNED; }
  static inline MPI_Datatype map(long) { return MPI_LONG; }
  static inline MPI_Datatype map(unsigned long) { return MPI_UNSIGNED_LONG; }
  static inline MPI_Datatype map(long long) { return MPI_LONG_LONG; }
  static inline MPI_Datatype map(unsigned long long) { return MPI_UNSIGNED_LONG_LONG; }
  static inline MPI_Datatype map(float) { return MPI_FLOAT; }
  static inline MPI_Datatype map(double) { return MPI_DOUBLE; }
  static inline MPI_Datatype map(long double) { return MPI_LONG_DOUBLE; }

  // Método plantilla para enviar un valor
  template <typename DataType>
  void send(const DataType& value, int toProcess, int tag = 0) const {
