#Variables
nota = int(input("Ingrese la nota del estudiante (sobre 100): "))

#Ciclo
if nota > 90:
    print("Excelente")
else:
    if nota >= 80 and nota <= 89:
        print("Buena")
    else:
        if nota >= 70 and nota <= 79:
            print("Pasable")
        else:
            print("Insuficiente")
