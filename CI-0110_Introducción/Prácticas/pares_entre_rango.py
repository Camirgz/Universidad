"""
Práctica: Generación de números pares en un rango
Genera todos los números pares estrictamente entre dos valores dados
"""


def pares_en_rango(a, b):
    """
    Genera lista de números pares entre a y b (exclusivo).

    Args:
        a: Límite inferior (exclusivo)
        b: Límite superior (exclusivo)

    Returns:
        Lista de números pares entre a y b, o None si a >= b
    """
    if a >= b:
        return None

    # Ajustar inicio al siguiente número par
    inicio = a + 1
    if inicio % 2 == 0:
        inicio += 1

    return list(range(inicio, b, 2))


def main():
    """Lee dos números y muestra todos los números pares entre ellos."""
    a = int(input("Ingrese el primer número: "))
    b = int(input("Ingrese el segundo número: "))

    numeros = pares_en_rango(a, b)

    if numeros is None:
        print("El valor de a debe ser menor que el valor de b")
    else:
        print(f"Los números pares estrictamente mayores a {a} y estrictamente menores a {b} son:")
        print(numeros)


if __name__ == "__main__":
    main()
