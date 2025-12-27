"""
Práctica: Generación de números en un rango
Genera todos los números estrictamente entre dos valores dados
"""


def numeros_en_rango(a, b):
    """
    Genera lista de números entre a y b (exclusivo).

    Args:
        a: Límite inferior (exclusivo)
        b: Límite superior (exclusivo)

    Returns:
        Lista de números entre a y b, o None si a >= b
    """
    if a >= b:
        return None
    return list(range(a + 1, b))


def main():
    """Lee dos números y muestra todos los números entre ellos."""
    a = int(input("Ingrese el primer número (a): "))
    b = int(input("Ingrese el segundo número (b): "))

    numeros = numeros_en_rango(a, b)

    if numeros is None:
        print("El valor de a debe ser menor que el valor de b")
    else:
        print(f"Los números estrictamente mayores a {a} y estrictamente menores a {b} son:")
        print(numeros)


if __name__ == "__main__":
    main()
