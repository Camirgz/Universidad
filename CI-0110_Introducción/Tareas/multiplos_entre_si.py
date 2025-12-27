"""
Tarea: Verificador de Múltiplos (Unidireccional)
Verifica si el primer número es múltiplo del segundo
"""


def es_multiplo(numero_a, numero_b):
    """
    Verifica si numero_a es múltiplo de numero_b.

    Args:
        numero_a: Número a verificar
        numero_b: Divisor

    Returns:
        True si numero_a es múltiplo de numero_b, False en caso contrario
    """
    return numero_a % numero_b == 0


def main():
    """Lee dos números y verifica si el primero es múltiplo del segundo."""
    numero_a = int(input("Digite un número: "))
    numero_b = int(input("Digite otro número: "))

    if es_multiplo(numero_a, numero_b):
        print(f"{numero_a} es múltiplo de {numero_b}")
    else:
        print(f"{numero_a} no es múltiplo de {numero_b}")


if __name__ == "__main__":
    main()
