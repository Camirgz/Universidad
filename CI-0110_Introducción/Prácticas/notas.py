"""
Práctica: Clasificación de notas
Clasifica una nota numérica en categorías: Excelente, Buena, Pasable o Insuficiente
"""


def clasificar_nota(nota):
    """
    Clasifica una nota en una categoría.

    Args:
        nota: Nota numérica sobre 100

    Returns:
        Clasificación de la nota
    """
    if nota > 90:
        return "Excelente"
    elif 80 <= nota <= 89:
        return "Buena"
    elif 70 <= nota <= 79:
        return "Pasable"
    else:
        return "Insuficiente"


def main():
    """Lee una nota y la clasifica."""
    nota = int(input("Ingrese la nota del estudiante (sobre 100): "))
    clasificacion = clasificar_nota(nota)
    print(clasificacion)


if __name__ == "__main__":
    main()
