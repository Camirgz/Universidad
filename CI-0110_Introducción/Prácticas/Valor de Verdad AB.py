#Variables
decision = True
user = " "
options = ["A","B"]

while decision:
	user = str(input("Digite un carácter: ")) 
	user = user.upper()
	if user in options:
		print("Gracias")
		decision = False
