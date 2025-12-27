# Multiplos entre si

numeroA = int(input("Digite un número: "))
numeroB = int(input("Digite otro número: "))

#Ciclo de A con respecto a B
if numeroA % numeroB == 0:
    print(numeroA, "es múltiplo de ", numeroB)
else:
    print(numeroA, "no es múltiplo de ", numeroB)

#Ciclo de B con respecto a A
if numeroB % numeroA == 0:
    print(numeroB, "es múltiplo de ", numeroA)
else:
    print(numeroB, "no es múltiplo de ", numeroA)
