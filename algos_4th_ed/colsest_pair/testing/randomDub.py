import random
# from datetime import datetime
import time


with open("32Kdoubles.txt", 'w') as outF:
    random.seed(time.time() * 1000)
    for x in xrange(0,32000):
        outF.write(str(random.uniform(1.5, 10000000.9)))
        outF.write("\n")
