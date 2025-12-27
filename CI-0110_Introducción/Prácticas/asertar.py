"""
Práctica: Ciclo con condición de salida
Lee números del usuario hasta que ingrese -1
"""


def main():
    """Lee números hasta que el usuario ingrese -1."""
    numero = 0

    while numero != -1:
        numero = int(input("Digite un número (-1 para terminar): "))

    print("Programa terminado")


if __name__ == "__main__":
    main()
