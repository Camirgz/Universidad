"""
Práctica: Búsqueda del número menor
Lee tres números y determina cuál es el menor de ellos
"""


def encontrar_menor(num1, num2, num3):
    """
    Encuentra el menor de tres números.

    Args:
        num1: Primer número
        num2: Segundo número
        num3: Tercer número

    Returns:
        El número menor
    """
    return min(num1, num2, num3)


def main():
    """Lee tres números y muestra el menor."""
    num1 = int(input("Digite un número: "))
    num2 = int(input("Digite un número: "))
    num3 = int(input("Digite un número: "))

    menor = encontrar_menor(num1, num2, num3)
    print("El número menor es", menor)


if __name__ == "__main__":
    main()
