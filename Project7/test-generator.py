import random

letters = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']

filename = "test7.blip"
target = open(filename, 'w')

for i in range(1000):
	string = "var " 
	howManyLetters = i//26
	if (howManyLetters < 130):
		for k in range(howManyLetters + 1):
			varName = letters[random.randrange(0, 26)]
			string += varName
	else:
		for k in range(130):
			varName = letters[random.randrange(0, 26)]
			string += varName

	string += " "
	string += str(random.randrange(0, 1000))
	target.write(string)
	target.write("\n")
	string = ""

target.write("text \n")
target.close()