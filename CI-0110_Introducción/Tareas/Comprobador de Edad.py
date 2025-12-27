treintaa = False
cincuentaa = False

while not (treintaa or cincuentaa):
  nombre = input("Ingrese el nombre: ")
  edad = int(input("Ingrese la edad: "))
  if edad == 30:
    treintaa = True
  elif edad == 50:
    cincuentaa = True

print("Ha ingresado al menos una una persona con 50 años o una con 30 años ")
