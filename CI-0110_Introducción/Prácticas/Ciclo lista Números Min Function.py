#Variables
cant_num  = int(input("Digite la cantidad de números que desea ingresar: "))
list_num = []
newlist = []

#Ciclo de creación de lista
for x in range(cant_num):
    num = int(input("Ingrese un número: "))
    list_num.append(num)

#Ciclo de orden
for i in range(len(list_num)):
    minimun = min(list_num)
    newlist.append(minimun)
    list_num.remove(minimun)

#Impresión
print(newlist)
