"""
Práctica: Clasificador de Vocales
Determina si un carácter es vocal, consonante o no es una letra
"""

VOCALES = {'a', 'e', 'i', 'o', 'u'}


def es_vocal(caracter):
    """
    Determina si un carácter es una vocal.

    Args:
        caracter: Carácter a verificar

    Returns:
        True si es vocal, False en caso contrario
    """
    return caracter.lower() in VOCALES


def main():
    """Lee una letra y determina si es vocal o consonante."""
    letra = input("Ingrese una letra: ")

    if not letra.isalpha() or len(letra) != 1:
        print("El valor ingresado no es una letra válida")
    elif es_vocal(letra):
        print("La letra ingresada es una vocal")
    else:
        print("La letra ingresada es una consonante")


if __name__ == "__main__":
    main()
