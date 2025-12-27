"""
Práctica: Clasificación de números por signo
Determina si un número es positivo, negativo o cero
"""


def clasificar_numero(numero):
    """
    Clasifica un número según su signo.

    Args:
        numero: Número a clasificar

    Returns:
        Clasificación del número: "positivo", "negativo" o "cero"
    """
    if numero > 0:
        return "positivo"
    elif numero == 0:
        return "cero"
    else:
        return "negativo"


def main():
    """Lee un número y lo clasifica por su signo."""
    numero = int(input("Digite un número: "))
    clasificacion = clasificar_numero(numero)
    print(f"El número es {clasificacion}")


if __name__ == "__main__":
    main()
