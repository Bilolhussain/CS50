import cs50
from cs50 import get_int

def main():

    # get pyramid size and check if not within limits
    while True:
        print("Height: ", end = "")
        height = cs50.get_int()
        if height >= 0 and height <= 23:
            break
        elif height < 0:
            print("Number should be greater than 0")

    #print out that many blocks
    #row defines rows
    for row in range(0, height):
            for column in range (0, (height - (row + 1))):
                print(" ", end = "")

            for column  in range ((height - (row + 1)), (height)):
                print("#", end = "")

            for column  in range(height, (height + 2)):
                print(" ", end = "")

            for column  in range(height + 2, (height + 3 + row) ):
                print("#", end = "")
    #ensures line break between the rows
            print()



if __name__ == "__main__":
    main()
