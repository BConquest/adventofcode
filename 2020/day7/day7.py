#/bin/python3
import sys

def parseInput(line):
    removal = ["bag", "bag,", "bag.", "bags", "bags,", "bags."]
    return [word for word in line if word not in removal]

def printData(data):
    for d in data:
        print(d)

def findGoldBags(data):
    for line in lines:
        if "shiny gold bag" in line or "shiny gold bags" in line:
            print(line, end="")
    
def getContainerBag(line):
    words = line.split()
    print(words[3])

def main():
    data = open(sys.argv[1]).readlines()
    for i,line in enumerate(data):
        data[i] = parseInput(line.split())
    
    printData(data)

main()
