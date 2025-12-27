"""
Práctica: Ciclo con acumulación
Lee números del usuario hasta que ingrese -1 y calcula la suma total
"""


def main():
    """Lee números hasta que el usuario ingrese -1 y muestra la suma."""
    numero = 0
    suma = 0

    while numero != -1:
        numero = int(input("Digite un número (-1 para terminar): "))
        suma += numero

    print("Programa terminado")
    print("La suma es", suma)


if __name__ == "__main__":
    main()
