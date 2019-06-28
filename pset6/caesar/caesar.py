import cs50
import sys
from cs50 import get_string


def main():

    # checks whether arguments given are equal to 2
    if len(sys.argv) != 2:
        sys.exit(1)

    else:
        # saves argument as key
        key = sys.argv[1]
        ciphertext = 0
        c = 0
        c = int(key)
        # if key is greater than 1 encrypt
        if (c < 1):
            print("key must be greater than 1")
            sys.exit(1)

        print("plaintext:")
        plaintext = cs50.get_string()
        print("ciphertext: ", end="")

        # converts text to ciphertext
        for i in range(len(plaintext)):
            # checks whether plaintext is small letters and converts accordingly
            if(plaintext[i] >= 'a' and plaintext[i] <= 'z'):
                ciphertext = (ord(plaintext[i])) - 97
                e = (((ciphertext + c) % 26) + 97)
                print(chr(e), end="")

            # checks whether plaintext is all capital letters and converts accordingly
            elif(plaintext[i] >= 'A' and plaintext[i] <= 'Z'):
                ciphertext = (ord(plaintext[i]) - 65)
                e = (((ciphertext + c) % 26) + 65)
                print(chr(e), end="")

            else:
                print(plaintext[i], end="")
        print()
        sys.exit(0)


if __name__ == "__main__":
    main()
