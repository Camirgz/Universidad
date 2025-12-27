"""
Tarea: Verificador de Divisibilidad entre 7
Determina si un número es múltiplo de 7
"""


def es_multiplo_de_siete(numero):
    """
    Verifica si un número es múltiplo de 7.

    Args:
        numero: Número a verificar

    Returns:
        True si es múltiplo de 7, False en caso contrario
    """
    return numero % 7 == 0


def main():
    """Lee un número y verifica si es múltiplo de 7."""
    numero = int(input("Digite un número: "))

    if es_multiplo_de_siete(numero):
        print("El número es múltiplo de 7")
    else:
        print("El número no es múltiplo de 7")


if __name__ == "__main__":
    main()
