#Variables
cant_num  = int(input("Digite la cantidad de números que desea ingresar: "))
list_num = []

#Ciclo
for x in range(cant_num):
    num = int(input("Ingrese un número: "))
    list_num.append(num)

#Impresión
list_num.sort()
print(list_num)
