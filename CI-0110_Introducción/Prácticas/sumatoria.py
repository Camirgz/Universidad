"""
Práctica: Cálculo de sumatoria
Calcula la suma de todos los números desde 0 hasta N
"""


def calcular_sumatoria(n):
    """
    Calcula la suma de números desde 0 hasta n.

    Args:
        n: Límite superior de la sumatoria

    Returns:
        Suma de 0 + 1 + 2 + ... + n
    """
    return sum(range(n + 1))


def main():
    """Lee un número N y calcula la suma de 0 a N."""
    numero = int(input("Digite el último número de la suma: "))
    resultado = calcular_sumatoria(numero)
    print(resultado)


if __name__ == "__main__":
    main()
