"""
Práctica: Determinación de cuadrantes cartesianos
Dados valores de x e y, determina en qué cuadrante se encuentra el punto
"""


def determinar_cuadrante(x, y):
    """
    Determina el cuadrante de un punto en el plano cartesiano.

    Args:
        x: Coordenada x del punto
        y: Coordenada y del punto

    Returns:
        Número del cuadrante (I, II, III, o IV)
    """
    if x > 0 and y > 0:
        return "I"
    elif x > 0 and y < 0:
        return "IV"
    elif x < 0 and y < 0:
        return "III"
    elif x < 0 and y > 0:
        return "II"
    else:
        return None


def main():
    """Lee coordenadas x, y y determina el cuadrante."""
    x = int(input("Digite el valor de x: "))
    y = int(input("Digite el valor de y: "))

    cuadrante = determinar_cuadrante(x, y)

    if cuadrante:
        print(f"{cuadrante} cuadrante")
    else:
        print("El punto está sobre un eje")


if __name__ == "__main__":
    main()
