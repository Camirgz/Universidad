# Multiplos entre si

numeroA = int(input("Digite un número: "))
numeroB = int(input("Digite otro número: "))

if numeroA % numeroB == 0:
    print(numeroA, "es múltiplo de ", numeroB)
else:
    print(numeroA, "no es múltiplo de ", numeroB)
