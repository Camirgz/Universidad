"""
Práctica: Ordenamiento de lista usando función min()
Lee números del usuario y los ordena usando la función min() iterativamente
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


def ordenar_con_min(numeros):
    """
    Ordena una lista extrayendo el mínimo iterativamente.

    Args:
        numeros: Lista de números a ordenar

    Returns:
        Nueva lista con los números ordenados
    """
    lista_ordenada = []
    lista_temporal = numeros.copy()

    while lista_temporal:
        minimo = min(lista_temporal)
        lista_ordenada.append(minimo)
        lista_temporal.remove(minimo)

    return lista_ordenada


def main():
    """Lee números del usuario y los muestra ordenados usando min()."""
    cantidad = int(input("Digite la cantidad de números que desea ingresar: "))
    numeros = leer_numeros(cantidad)
    numeros_ordenados = ordenar_con_min(numeros)
    print("Números ordenados:", numeros_ordenados)


if __name__ == "__main__":
    main()
