"""
Tarea: Verificador de Múltiplos (Bidireccional)
Verifica si A es múltiplo de B y si B es múltiplo de A
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


def verificar_multiplos_bidireccional(a, b):
    """
    Verifica múltiplos en ambas direcciones.

    Args:
        a: Primer número
        b: Segundo número

    Returns:
        Tupla de booleanos (a_es_multiplo_de_b, b_es_multiplo_de_a)
    """
    return (es_multiplo(a, b), es_multiplo(b, a))


def main():
    """Lee dos números y verifica múltiplos en ambas direcciones."""
    numero_a = int(input("Digite un número: "))
    numero_b = int(input("Digite otro número: "))

    # Verificar A con respecto a B
    if es_multiplo(numero_a, numero_b):
        print(f"{numero_a} es múltiplo de {numero_b}")
    else:
        print(f"{numero_a} no es múltiplo de {numero_b}")

    # Verificar B con respecto a A
    if es_multiplo(numero_b, numero_a):
        print(f"{numero_b} es múltiplo de {numero_a}")
    else:
        print(f"{numero_b} no es múltiplo de {numero_a}")


if __name__ == "__main__":
    main()
