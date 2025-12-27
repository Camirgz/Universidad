// Copyright 2024 ECCI-UCR CC-BY-4
#pragma once

#include <mpi.h>
#include <stdexcept>
#include <string>
#include <vector>

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
  class Error : public std::runtime_error {
   public:
    explicit Error(const std::string& message)
      : std::runtime_error(message) {
    }
    Error(const std::string& message, const Mpi& mpi)
      : std::runtime_error(mpi.getHostname() + ':' + std::to_string(mpi.rank())
        + ": " + message) {
    }
    Error(const std::string& message, const Mpi& mpi, const int threadNumber)
      : std::runtime_error(mpi.getHostname() + ':' + std::to_string(mpi.rank())
        + '.' + std::to_string(threadNumber) + ": " + message) {
    }
  };

 public:
  Mpi(int& argc, char**& argv) {
    if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
      throw Error("could not init MPI");
    }
    if (MPI_Comm_rank(MPI_COMM_WORLD, &this->processNumber) != MPI_SUCCESS) {
      throw Error("could not get MPI rank");
    }
    if (MPI_Comm_size(MPI_COMM_WORLD, &this->processCount) != MPI_SUCCESS) {
      throw Error("could not get MPI size");
    }
    char processHostname[MPI_MAX_PROCESSOR_NAME] = { '\0' };
    int hostnameLen = -1;
    if (MPI_Get_processor_name(processHostname, &hostnameLen) != MPI_SUCCESS) {
      throw Error("could not get processor name");
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

 public:
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

 public:  // Send
  /// Send a scalar value to another process
  template <typename Type>
  void send(const Type& value, const int toProcess, const int tag = 0) {
    return this->send(&value, /*count*/ 1, toProcess, tag, "value");
  }
  /// Send an array of count values to another process
  template <typename Type>
  void send(const Type* values, const int count, const int toProcess,
      const int tag = 0) {
    return this->send(values, count, toProcess, tag, "array");
  }
  /// Send a mutable array of count values to another process
  template <typename Type>
  void send(Type* values, const int count, const int toProcess,
      const int tag = 0) {
    return this->send(values, count, toProcess, tag, "array");
  }
  /// Send an array of values to another process
  template <typename Type>
  void send(const std::vector<Type>& values, const int toProcess,
      const int tag = 0) {
    return this->send(values.data(), values.size(), toProcess, tag, "vector");
  }
  /// Send a text to another process
  void send(const std::string& text, const int toProcess, const int tag = 0) {
    return this->send(text.data(), text.size() + 1, toProcess, tag, "string");
  }

 private:
  template <typename Type>
  void send(const Type* values, const int count, const int toProcess,
      const int tag, const std::string& type) {
    if (count <= 0) {
      throw Error("invalid count of elements to send", *this);
    }
    if (MPI_Send(values, count, Mpi::map(values[0]), toProcess,
        tag, MPI_COMM_WORLD) != MPI_SUCCESS) {
      throw Error("could not send " + type, *this);
    }
  }
  template <typename Type>
  int receive(Type* values, const int capacity,
    const int fromProcess, const int tag, const std::string& type) {
    if (capacity <= 0) {
      throw Error("invalid capacity to receive data", *this);
    }
    MPI_Status status;
    if (MPI_Recv(values, capacity, Mpi::map(Type()), fromProcess, tag,
        MPI_COMM_WORLD, &status) != MPI_SUCCESS) {
      throw Mpi::Error("could not receive " + type, *this);
    }
    int count = -1;
    if (MPI_Get_count(&status, Mpi::map(Type()), &count) != MPI_SUCCESS) {
      throw Mpi::Error("could not receive count of " + type, *this);
    }
    return count;
  }

 public:  // Receive
  /// Wait until it receives a scalar value from other process
  template <typename Type>
  int receive(Type& value, const int fromProcess,
      const int tag = MPI_ANY_TAG) {
    return this->receive(&value, /*capacity*/ 1, fromProcess, tag, "value");
  }
  /// Wait until it receives at most capacity values from another process
  template <typename Type>
  int receive(Type* values, const int capacity,
      const int fromProcess = MPI_ANY_SOURCE, const int tag = MPI_ANY_TAG) {
    return this->receive(values, capacity, fromProcess, tag, "array");
  }
  /// Wait until it receives at most capacity values from another process
  template <typename Type>
  int receive(std::vector<Type>& values, const int capacity,
      const int fromProcess = MPI_ANY_SOURCE, const int tag = MPI_ANY_TAG) {
    if (static_cast<int>(values.size()) <= capacity) {
      values.resize(capacity);
    }
    return this->receive(values.data(), capacity, fromProcess, tag, "vector");
  }
  /// Wait until it receives a text of at most length chars from another process
  int receive(std::string& text, const int capacity,
      const int fromProcess = MPI_ANY_SOURCE, const int tag = MPI_ANY_TAG) {
    std::vector<char> buffer(capacity, '\0');
    const int count = this->receive(buffer, capacity, fromProcess, tag);
    text = buffer.data();
    return count;
  }

 public:
  class MpiStream {
   private:
    Mpi& mpi;
    const int process;

   public:
    MpiStream(Mpi& mpi, const int process)
      : mpi(mpi)
      , process(process) {
    }
    template <typename Type>
    MpiStream& operator<<(const Type& value) {
      this->mpi.send(value, this->process);
      return *this;
    }
    template <typename Type>
    MpiStream& operator>>(Type& variable) {
      this->mpi.receive(variable, this->process);
      return *this;
    }
  };
  inline MpiStream operator[](const int process) {
    return MpiStream(*this, process);
  }

 public:
  void barrier() {
    if (MPI_Barrier(MPI_COMM_WORLD) != MPI_SUCCESS) {
      throw Mpi::Error("could not wait barrier", *this);
    }
  }

  inline double wtime() const {
    return MPI_Wtime();
  }

 public:  // Broadcast
  /// Broadcast a scalar value to all other processes
  template <typename Type>
  void broadcast(Type& value, const int fromProcess) {
    if (MPI_Bcast(&value, /*count*/ 1, Mpi::map(value), fromProcess,
        MPI_COMM_WORLD) != MPI_SUCCESS) {
      throw Mpi::Error("could not broadcast value", *this);
    }
  }

 public:
  /// Reduce a scalar value to one process
  template <typename Type>
  void reduce(const Type& value, Type& result, const MPI_Op operation,
      const int toProcess) {
    if (MPI_Reduce(&value, &result, /*count*/ 1, Mpi::map(value),
        operation, toProcess, MPI_COMM_WORLD) != MPI_SUCCESS) {
      throw Mpi::Error("could not reduce value", *this);
    }
  }

 public:
  /// Reduce a scalar value to all processes
  template <typename Type>
  void allReduce(const Type& value, Type& result, const MPI_Op operation) {
    if (MPI_Allreduce(&value, &result, /*count*/ 1, Mpi::map(value),
        operation, MPI_COMM_WORLD) != MPI_SUCCESS) {
      throw Mpi::Error("could not all-reduce value", *this);
    }
  }
};

