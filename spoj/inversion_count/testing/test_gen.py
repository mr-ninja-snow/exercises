import random

num = 16
testCaseList = random.sample(range(1, num), num -1)

with open("16_range.txt", 'w') as outfile:
	for el in testCaseList:
		outfile.write(str(el) + "\n")