import random

with open("bitonic2ElCenterLeft32KInts.txt", 'w') as outF:
    random.seed(time.time() * 1000)
    ran_list = random.sample(range(1, 1000000), 32000)

    ran_list.sort()

    numOfEls = len(ran_list)/2
    numOfEls = 3

    newList = list()
    curIndex = 0
    for x in xrange(1,numOfEls):
        var = ran_list[curIndex]
        del ran_list[curIndex]
        newList.append(var)
        curIndex += 1

    ran_list.reverse()
    bitonicList = newList + ran_list

    for el in bitonicList:
        outF.write(str(el))
        outF.write("\n")