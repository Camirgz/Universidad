#Variables
x = int(input("Digite el valor de x: "))
y = int(input("Digite el valor de y: "))

xpos = False
ypos = False


if x > 0: xpos = True
if y > 0: ypos = True

if xpos and ypos :
	print("I cuadrante")
elif xpos and not ypos:
	print("II cuadrante")
elif not xpos and not ypos:
	print("III cuadrante")
elif ypos and not xpos :
	print("IV cuadrante")
