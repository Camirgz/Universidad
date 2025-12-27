# Definición de variables
menu = 0
firstnum = 0
secondnum = 0
operation = 0
keepgoing = 0

# Bucle while
while keepgoing == 0:
    print("Bienvenido a la calculadora")
    print("Digite la acción que desea realizar")
    
    # Solicitar la acción al usuario
    menu = input("1. Suma\n2. Resta\n3. Multiplicación\n4. Dividir\n5. Salir\n")
    
    # Verificar si la entrada es un número
    if not menu.isdigit():
        print("Debe digitar un número")
        continue
    
    menu = int(menu)
    
    if menu == 1:
        firstnum = int(input("Digite el primer número: "))
        secondnum = int(input("Digite el segundo número: "))
        operation = firstnum + secondnum
        print(f"El resultado es {operation}")
    
    elif menu == 2:
        firstnum = int(input("Digite el primer número: "))
        secondnum = int(input("Digite el segundo número: "))
        operation = firstnum - secondnum
        print(f"El resultado es {operation}")
    
    elif menu == 3:
        firstnum = int(input("Digite el primer número: "))
        secondnum = int(input("Digite el segundo número: "))
        
        if secondnum != 0:
            operation = firstnum / secondnum
            print(f"El resultado es {operation}")
        else:
            print("La división entre 0 no existe")
            continue
    
    elif menu == 4:
        firstnum = int(input("Digite el primer número: "))
        secondnum = int(input("Digite el segundo número: "))
        operation = firstnum * secondnum
        print(f"El resultado es {operation}")
    
    elif menu == 5:
        keepgoing = 1
        print("Gracias!")
    
    else:
        print("Opción inválida")
