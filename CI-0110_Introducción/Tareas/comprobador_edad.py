"""
Tarea: Comprobador de Edad
Lee personas hasta encontrar alguien con 30 años o alguien con 50 años
"""


def main():
    """Lee nombres y edades hasta encontrar una persona con 30 o 50 años."""
    tiene_treinta = False
    tiene_cincuenta = False

    while not (tiene_treinta or tiene_cincuenta):
        nombre = input("Ingrese el nombre: ")
        edad = int(input("Ingrese la edad: "))

        if edad == 30:
            tiene_treinta = True
        elif edad == 50:
            tiene_cincuenta = True

    print("Ha ingresado al menos una persona con 50 años o una con 30 años")


if __name__ == "__main__":
    main()
