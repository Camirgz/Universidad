#Variables
letra = input("Ingrese una letra: ").lower()

#Lista con Vocales
vocales = ['a', 'e', 'i', 'o', 'u']

#Ciclo
if letra.isalpha():
    if letra in vocales:
        print("La letra ingresada es una vocal")
    else:
        print("La letra ingresada es una consonante")
else:
    print("El valor ingresado no es una letra")
