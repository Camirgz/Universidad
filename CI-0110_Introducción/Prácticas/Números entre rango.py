#Variables
a = int(input("Ingrese el primer número (a): "))
b = int(input("Ingrese el segundo número (b): "))

#Ciclo con lista
if a < b:
    numeros = [i for i in range(a+1, b) if i > a and i < b]
    print("Los números estrictamente mayores a", a, "y estrictamente menores a", b, "son:")
    print(numeros)
else:
    print("El valor de a debe ser menor que el valor de b")

