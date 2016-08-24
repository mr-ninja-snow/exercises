class NumberKeeper(object):
	"""docstring for NumberKeeper  """
	def __init__(self, secretNumber):
		self.secretNumber = secretNumber
		self.numberOfCmp = 0

	def numberCmp(self, baseNumber, number):
		self.numberOfCmp += 1
		if abs(baseNumber - self.secretNumber) < abs(number - self.secretNumber):
			return "cold"
		else:
			return "hot"

	def inSecretNumber(self, number):
		return number == self.secretNumber

	def getNumberOfCmp(self):
		return self.numberOfCmp

class HotColdBinarySolver(object):
	"""docstring for HotColdBinarySolver"""
	def __init__(self, min, max, numberKeeper):
		self.min = min
		self.max = max
		self.numberKeeper = numberKeeper
		# self.lastHotNumber = (max - min) / 2
		# self.leftHalf = (self.lastHotNumber - min) / 2
		# self.rightHalf = (max -self.lastHotNumber) / 2
		self.lastHotNumber = (max - min) / 2
		return self.solve(min, max)

	def solve(self, leftBorder, rightBorder):
		self.leftHalf = (self.lastHotNumber - leftBorder) / 2
		self.rightHalf = (rightBorder - self.lastHotNumber) / 2

		if self.numberKeeper.numberCmp(self.lastHotNumber, self.leftHalf) == "hot":
			tmp = self.lastHotNumber
			self.lastHotNumber = self.leftHalf
			return self.solve(self.leftBorder, tmp)

		if self.numberKeeper.numberCmp(self.lastHotNumber, self.rightHalf) == "hot":
			tmp = self.lastHotNumber
			self.lastHotNumber = self.leftHalf
			return self.solve(self.leftBorder, tmp)

		return None

def main():
	

if __name__ == '__main__':
	main()