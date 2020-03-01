from cs50 import get_string
from sys import argv
import string
import sys


def main():

    # 1.0 check if key is alphabetical
    if argv[1].isalpha() == False or len(sys.argv) > 2:
        print("Usage: python vigenere.py k")
        sys.exit(1)

    # 2.0 prompt user for plaintext
    text = list(get_string("plaintext: "))

    # 3.0 vigenere cipher algorithm
    # 3.1 get key from command line argument
    key = list(argv[1])

    # 3.2 convert alphabetic key to cipher index (a = 0, b = 1, ... z = 25)
    for i in range(len(key)):
        if key[i].isupper() == True:
            key[i] = ord(key[i]) - 65
        else:
            key[i] = ord(key[i]) - 97

    # 3.3 iterate over plaintext and encipher
    keyCounter = 0
    for i in range(len(text)):
        if text[i].isalpha() == True and text[i].isupper() == True:
            # c = (p + k) % 26
            text[i] = chr((ord(text[i]) + key[keyCounter] - 65) % 26 + 65)
            keyCounter = (keyCounter + 1) % len(key)

        elif text[i].isalpha() == True and text[i].islower() == True:
            text[i] = chr((ord(text[i]) + key[keyCounter] - 97) % 26 + 97)
            keyCounter = (keyCounter + 1) % len(key)

    print("ciphertext: " + "".join(text))


if __name__ == "__main__":
    main()