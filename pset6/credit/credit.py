from cs50 import get_int


def main():
    # get credit number of valid length
    creditCard = validCardInit()
    # validation for input length
    if creditCard == False:
        print("INVALID")
        return

    # perform checksum algorithm
    creditCard[2] = checkSum(creditCard[0])

    # output card type or invalid number
    if creditCard[2] == True:
        print(creditCard[1])
    else:
        print("INVALID")


def validCardInit():
    # prompt user for card number(int) and convert to string for subscripting and len()
    cardNumber = str(get_int("Number: "))

    if (len(cardNumber) == 13 or len(cardNumber) == 16) and cardNumber[0] == '4':
        card = [cardNumber, "VISA", False]
        return card

    elif len(cardNumber) == 15 and (cardNumber[:2] == '34' or cardNumber[:2] == '37'):
        card = [cardNumber, "AMEX", False]
        return card

    elif len(cardNumber) == 16 and cardNumber[:2] >= '51' and cardNumber[:2] <= '55':
        card = [cardNumber, "MASTERCARD", False]
        return card
    else:
        return False


def checkSum(cardNumber):
    checkSumValue = 0

    for i in range(1, len(cardNumber) + 1):
        if i % 2 == 1:
            # do this if index is an odd number
            checkSumValue += int(cardNumber[-i])
        else:
            # do this if index is an even number
            product_int = int(cardNumber[-i]) * 2
            product_str = str(product_int)

            if len(product_str) == 2:
                checkSumValue += int(product_str[0]) + int(product_str[1])
            else:
                checkSumValue += product_int

    if checkSumValue % 10 == 0:
        return True
    else:
        return False


if __name__ == "__main__":
    main()