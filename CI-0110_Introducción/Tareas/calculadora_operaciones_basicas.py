"""
Tarea: Calculadora de Operaciones Básicas
Implementa una calculadora simple con suma, resta, multiplicación y división
"""


def suma(a, b):
    """Retorna la suma de dos números."""
    return a + b


def resta(a, b):
    """Retorna la resta de dos números."""
    return a - b


def multiplicacion(a, b):
    """Retorna la multiplicación de dos números."""
    return a * b


def division(a, b):
    """
    Retorna la división de dos números.

    Args:
        a: Dividendo
        b: Divisor

    Returns:
        Resultado de la división o None si el divisor es cero
    """
    if b == 0:
        return None
    return a / b


def leer_numeros():
    """Lee dos números del usuario."""
    primer_numero = int(input("Digite el primer número: "))
    segundo_numero = int(input("Digite el segundo número: "))
    return primer_numero, segundo_numero


def mostrar_menu():
    """Muestra el menú de opciones y retorna la opción seleccionada."""
    print("\nBienvenido a la calculadora")
    print("Digite la acción que desea realizar:")
    opcion = input("1. Suma\n2. Resta\n3. Multiplicación\n4. División\n5. Salir\n> ")
    return opcion


def ejecutar_operacion(opcion):
    """
    Ejecuta la operación seleccionada.

    Args:
        opcion: Número de opción del menú

    Returns:
        False si el usuario quiere salir, True en caso contrario
    """
    if opcion == "1":
        num1, num2 = leer_numeros()
        print(f"El resultado es {suma(num1, num2)}")

    elif opcion == "2":
        num1, num2 = leer_numeros()
        print(f"El resultado es {resta(num1, num2)}")

    elif opcion == "3":
        num1, num2 = leer_numeros()
        print(f"El resultado es {multiplicacion(num1, num2)}")

    elif opcion == "4":
        num1, num2 = leer_numeros()
        resultado = division(num1, num2)
        if resultado is None:
            print("Error: La división entre 0 no está definida")
        else:
            print(f"El resultado es {resultado}")

    elif opcion == "5":
        print("¡Gracias por usar la calculadora!")
        return False

    else:
        print("Opción inválida")

    return True


def main():
    """Función principal que ejecuta la calculadora."""
    continuar = True

    while continuar:
        opcion = mostrar_menu()

        if not opcion.isdigit():
            print("Debe digitar un número")
            continue

        continuar = ejecutar_operacion(opcion)


if __name__ == "__main__":
    main()
