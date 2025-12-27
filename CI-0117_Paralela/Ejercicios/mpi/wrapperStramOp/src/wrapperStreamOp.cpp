#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <mpi.h>

// Declaración adelantada
class Mpi;

class MpiStream {
private:
    int target_rank;
    Mpi& mpi_ref;
    int next_tag;

public:
    MpiStream(int rank, Mpi& mpi, int start_tag = 0) 
        : target_rank(rank), mpi_ref(mpi), next_tag(start_tag) {}

    template<typename T>
    MpiStream& operator<<(const T& data) {
        mpi_ref.send(data, target_rank, next_tag);
        next_tag++;
        return *this;
    }

    template<typename T>
    MpiStream& operator>>(T& data) {
        mpi_ref.receive(data, target_rank, next_tag);
        next_tag++;
        return *this;
    }
};

class Mpi {
private:
    int my_rank;
    int total_size;
    int next_tag;

public:
    Mpi(int argc, char* argv[]) : next_tag(0) {
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &total_size);
    }

    ~Mpi() {
        MPI_Finalize();
    }

    int rank() const { return my_rank; }
    int size() const { return total_size; }

    MpiStream operator[](int target_rank) {
        if (target_rank < 0 || target_rank >= total_size) {
            throw std::out_of_range("Rango de proceso fuera de rango");
        }
        if (target_rank == my_rank) {
            throw std::invalid_argument("No se puede comunicar con el mismo proceso");
        }
        return MpiStream(target_rank, *this, next_tag);
    }

    template<typename T>
    void send(const T& data, int dest, int tag) {
        MPI_Send(&data, sizeof(T), MPI_BYTE, dest, tag, MPI_COMM_WORLD);
    }

    void send(const std::string& data, int dest, int tag) {
        int length = data.length();
        MPI_Send(&length, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
        MPI_Send(data.c_str(), length, MPI_CHAR, dest, tag + 1, MPI_COMM_WORLD);
    }

    template<typename T>
    void send(const std::vector<T>& data, int dest, int tag) {
        int size = data.size();
        MPI_Send(&size, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
        if (size > 0) {
            MPI_Send(data.data(), size * sizeof(T), MPI_BYTE, dest, tag + 1, MPI_COMM_WORLD);
        }
    }

    void send(const char* data, int dest, int tag) {
        send(std::string(data), dest, tag);
    }

    template<typename T>
    void receive(T& data, int source, int tag) {
        MPI_Status status;
        MPI_Recv(&data, sizeof(T), MPI_BYTE, source, tag, MPI_COMM_WORLD, &status);
    }

    void receive(std::string& data, int source, int tag) {
        MPI_Status status;
        int length;
        MPI_Recv(&length, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
        
        char* buffer = new char[length + 1];
        MPI_Recv(buffer, length, MPI_CHAR, source, tag + 1, MPI_COMM_WORLD, &status);
        buffer[length] = '\0';
        data = std::string(buffer);
        delete[] buffer;
    }

    template<typename T>
    void receive(std::vector<T>& data, int source, int tag) {
        MPI_Status status;
        int size;
        MPI_Recv(&size, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
        
        data.resize(size);
        if (size > 0) {
            MPI_Recv(data.data(), size * sizeof(T), MPI_BYTE, source, tag + 1, MPI_COMM_WORLD, &status);
        }
    }

    void barrier() {
        MPI_Barrier(MPI_COMM_WORLD);
    }
};

int main(int argc, char* argv[]) {
    try {
        Mpi mpi(argc, argv);

        if (mpi.rank() > 0) {
            std::string message = "Hello from process " + std::to_string(mpi.rank());
            mpi[0] << message;
            
            std::vector<int> numbers = {mpi.rank() * 10, mpi.rank() * 20, mpi.rank() * 30};
            mpi[0] << numbers;
        } else {
            std::cout << "Process 0 receiving messages..." << std::endl;
            for (int source = 1; source < mpi.size(); ++source) {
                std::string received_message;
                mpi[source] >> received_message;
                std::cout << "Process 0 received: " << received_message << std::endl;
                
                std::vector<int> received_numbers;
                mpi[source] >> received_numbers;
                std::cout << "Numbers from process " << source << ": ";
                for (int num : received_numbers) {
                    std::cout << num << " ";
                }
                std::cout << std::endl;
            }
        }

        mpi.barrier();

        if (mpi.rank() == 0 && mpi.size() > 1) {
            std::string confirmation = "Confirmation from process 0";
            mpi[1] << confirmation;
        } else if (mpi.rank() == 1) {
            std::string response;
            mpi[0] >> response;
            std::cout << "Process 1 received: " << response << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 1;
    }

    return 0;
}