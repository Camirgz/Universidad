"""
Práctica: Ordenamiento de lista de números
Lee una cantidad N de números y los muestra ordenados
"""


def leer_numeros(cantidad):
    """
    Lee una cantidad específica de números desde la entrada estándar.

    Args:
        cantidad: Número de elementos a leer

    Returns:
        Lista con los números ingresados
    """
    numeros = []
    for i in range(cantidad):
        numero = int(input(f"Ingrese el número {i + 1}: "))
        numeros.append(numero)
    return numeros


def main():
    """Lee números del usuario y los muestra ordenados."""
    cantidad = int(input("Digite la cantidad de números que desea ingresar: "))
    numeros = leer_numeros(cantidad)
    numeros.sort()
    print("Números ordenados:", numeros)


if __name__ == "__main__":
    main()
