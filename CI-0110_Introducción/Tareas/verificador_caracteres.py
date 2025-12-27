"""
Tarea: Verificador de Caracteres
Lee caracteres hasta que el usuario haya ingresado al menos una 'a' y una 'b'
"""


def main():
    """Lee caracteres hasta encontrar al menos una 'a' y una 'b'."""
    tiene_a = False
    tiene_b = False

    while not (tiene_a and tiene_b):
        caracter = input("Ingrese un caracter: ")

        if caracter == "a":
            tiene_a = True
        elif caracter == "b":
            tiene_b = True

    print("Ha ingresado al menos una 'a' y al menos una 'b'")


if __name__ == "__main__":
    main()
