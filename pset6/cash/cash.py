import cs50
from cs50 import get_int
from cs50 import get_float


def main():

    # values of coins
    quarter = 25
    dime = 10
    nickel = 5
    penny = 1

    # counter stores number of coins
    counter = 0

    # prompt user for cash
    print("Change owed?")
    Orignal = cs50.get_float()

    # checks if change is greater than 0
    while True:
        if Orignal <= 0:
            print("Try again")
            Orignal = cs50.get_float()

        if Orignal > 0:
            break

    # converts change to whole number
    C = Orignal * 100

    # breaks amount into different coins using minimum possible
    while True:
        if (C >= 25):
            C = C - quarter
            counter = counter + 1

        elif (C < 25 and C >= 10):
            C = C - dime
            counter = counter + 1

        elif (C < 10 and C >= 5):
            C = C - nickel
            counter = counter + 1

        elif (C < 5 and C > 0):

            C = C - penny
            counter = counter + 1

        elif C == 0:
            break

    print(counter)


if __name__ == "__main__":
    main()
