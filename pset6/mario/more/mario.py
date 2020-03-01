from cs50 import get_int


def main():
    # get height from user
    while True:
        height = get_int("Height: ")

        if height > 0 and height <= 8:
            break

    # print pyramid
    for i in range(1, height + 1):
        spaceCount = height - i

        # print spaces, then left pyramid, then 2-space gap, then right pyramid
        print(" " * spaceCount, "#" * i, "  ", "#" * i, sep="")


if __name__ == "__main__":
    main()