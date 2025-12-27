## Modificación de la clase `Mpi` para Envío y Recepción Punto a Punto

Modifique su clase `Mpi` en la carpeta `mpi_wrapper/` (no cree una nueva) para que pueda **enviar y recibir mensajes punto a punto** con métodos `send()` y `receive()`. La interfaz de estos y futuros métodos será similar al pseudocódigo propuesto para distribución (Pseudocódigo de paso de mensajes).

> **Nota:** Es deseable que la clase `Mpi` sea capaz de enviar y recibir valores de todos los tipos de datos primitivos soportados por MPI, **sin redundancia de código**. Evite implementar métodos separados para cada tipo de dato, como en el siguiente ejemplo:

```cpp
class Mpi {
    ...
 public:
    // MPI_CHAR, MPI_SIGNED_CHAR
    void send(const char& ch, int toProcess, int tag = 0);
    // MPI_UNSIGNED_CHAR, MPI_BYTE
    void send(const unsigned char& ch, int toProcess, int tag = 0);
    // MPI_SHORT...

 public:
    // MPI_CHAR, MPI_SIGNED_CHAR
    void receive(char& ch, int fromProcess, int tag = MPI_ANY_SOURCE);
    // MPI_UNSIGNED_CHAR, MPI_BYTE
    void receive(unsigned char& ch, int fromProcess, int tag = MPI_ANY_SOURCE);
    ...
};
```

Para evitar esta redundancia, **utilice programación genérica** mediante plantillas. La plantilla recibirá como parámetro el tipo de dato genérico a enviar o recibir por MPI. Sin embargo, la implementación de estos métodos debe invocar funciones de la biblioteca MPI que requieren constantes enteras específicas para cada tipo de dato.

Puede usar las siguientes subrutinas para mapear los tipos de datos primitivos de C++ a las constantes de MPI:

```cpp
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
```

Por ejemplo, `map(0.0)` se evaluará como `MPI_DOUBLE`, y `map(double())` también. Así, con un valor `value` de tipo `DataType`, puede obtener la constante de MPI correspondiente con `map(value)` o `map(DataType())`.

Implemente dos plantillas en su clase con la siguiente interfaz (en pseudocódigo):

- `send(value, toProcess, tag=0)`
- `receive(&value, fromProcess, tag=any_tag)`

La primera plantilla debe enviar un valor (referencia constante) del tipo de dato genérico usando `MPI_Send()`. La segunda plantilla debe recibir un valor y escribirlo en la variable proporcionada usando `MPI_Recv()`.

Con estos métodos, el ejemplo 47 se puede simplificar a:

```cpp
#include "../mpi_wrapper/Mpi.hpp"

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
        std::cout << "Hello from main thread of process " << rank << " of "
            << count << " on " << mpi.getHostname() << std::endl;
        mpi.send(can_print, next);
    } catch (const std::exception& error) {
        std::cerr << "error: " << error.what() << std::endl;
    }
}
```

Copie este código a un archivo `main.cpp` en una carpeta `mpi_wrapper_send_recv/`, asegúrese de que compila y produce los resultados esperados.