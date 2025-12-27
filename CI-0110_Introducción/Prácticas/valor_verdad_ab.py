"""
Práctica: Verificación de entrada de opciones
Lee caracteres hasta que el usuario ingrese 'A' o 'B' (case-insensitive)
"""


def main():
    """Lee caracteres hasta recibir 'A' o 'B'."""
    opciones_validas = {'A', 'B'}
    entrada_valida = False

    while not entrada_valida:
        caracter = input("Digite un carácter: ").upper()

        if caracter in opciones_validas:
            print("Gracias")
            entrada_valida = True


if __name__ == "__main__":
    main()
