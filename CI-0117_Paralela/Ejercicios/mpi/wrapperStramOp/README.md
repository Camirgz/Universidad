Permita enviar varios mensajes en secuencia a otro proceso utilizando el operador de flujo `<<` y recibir varios mensajes en secuencia de otro proceso con el operador `>>`. Para indicar el número de proceso, use el operador corchetes `[]`.

Por ejemplo, en el siguiente código, todos los procesos envían un saludo al proceso 0 compuesto de un texto y un número. El proceso 0 recibe el texto y el número de todos los demás procesos y los imprime en la salida estándar:

```cpp
if (mpi.rank() > 0) {
    mpi[0] << "Hello from " << mpi.rank();
} else {
    for (int source = 1; source < mpi.size(); ++source) {
        std::string text;
        int rank = 0;
        mpi[source] >> text >> rank;
        std::cout << source << " says: " << text << rank << std::endl;
    }
}
```

Haga que el operador `[]` retorne un objeto de una clase `MpiStream` que implemente los operadores de flujo. Este objeto debe tener como atributos el número de proceso con el que se hará la comunicación y una referencia al objeto `Mpi`. El operador corchetes debe lanzar una excepción si el número de proceso interlocutor está fuera de rango.

Implemente en la clase `MpiStream` operadores de flujo `<<` y `>>` genéricos (plantillas) que invoquen las versiones correspondientes de los métodos `send()` y `receive()` de la clase `Mpi`. La implementación del operador `>>` tendrá que hacer supuestos sobre el tamaño de los arreglos.