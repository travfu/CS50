from cs50 import get_string
from sys import argv
import sys


def main():

    # 1.0 validation
    # 1.1 validate command-line argument for 2 arg
    if len(sys.argv) != 2:
        print("Usage: python bleep.py dictionary")
        sys.exit(1)

    # 1.2 check for valid file
    filePath = argv[1]

    try:
        file = open(filePath, 'r')
    except:
        print("Error: File does not exist")
        sys.exit(1)

    # 2.0 store words from file in a set
    wordSet = set()

    for word in file:
        wordSet.add(word.replace("\n", ""))

    # 3.0 prompt user for text and store in list
    text = get_string("What message would you like to censor?\n").split(" ")

    # 4.0 censor texts if present in set
    for i in range(len(text)):
        if (text[i].lower() in wordSet) == True:
            text[i] = "*" * len(text[i])

    # 5.0 print censored text
    print(" ".join(text))


if __name__ == "__main__":
    main()
