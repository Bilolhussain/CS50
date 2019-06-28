#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{

    //checks if arguments given are equal to 2

    if (argc == 2)
    {
        //variable for plaintext algorithm calculation
        int b;
        //variable for key algorithm calculation
        int f;

        string key = (argv[1]);



        printf("plaintext: ");
        string text = get_string();
        printf("ciphertext: ");


        //if text is not empty
        if (text == NULL)
        {
            printf("No text given\n");
        }
        else
        {

            for (int i = 0, j = 0, m = strlen(key), n = strlen(text); i < n; i++)
            {



                //checks if text is lowercase and calculates char accordingly
                if ( text[i] >= 'a' && text[i] <= 'z' )
                {
                    //checks if key is lowercase and calculates key accordingly
                    if (key[j] >= 'a' && key [j] <= 'z' )
                    {
                        int e = key[j];
                        f = e - 97;

                    }
                    //checks if key is uppercase and calculates key accordingly

                    else if (key[j] >= 'A' && key [j] <= 'Z' )
                    {
                        int e = key[j];
                        f = e - 65;
                    }

                    //if key is not alphabetic give error(doesn't work for some reason)
                    else if (key[j] != isalpha(key[j]))
                    {
                        printf("Key Error");
                        return 1;
                    }

                    //computing ciphertext by manipulating text and key
                    int a = text[i];
                    b = a - 97;
                    char c = ((b + f) % 26) + 97;
                    printf("%c", c);
                    j = j + 1;
                    //loops key if key ends before text
                    key[j] = key[(j % m)];



                }
                //checks if text is uppercase and calculates char accordingly
                else if ( text[i] >= 'A' && text[i] <= 'Z' )
                {
                    //checks if key is lowercase and calculates char accordingly
                    if ( key[j] >= 'a' && key [j] <= 'z' )
                    {
                        int e = key[j];
                        f = e - 97;

                    }
                    //checks if key is uppercase and calculates char accordingly
                    else if ( key[j] >= 'A' && key [j] <= 'Z' )
                    {
                        int e = key[j];
                        f = e - 65;

                    }
                    else if (key[j] != isalpha(key[j]))
                    {
                        printf("Key Error");
                        return 1;
                    }

                    //computing ciphertext by manipulating text and key
                    int a = text[i];
                    b = a - 65;
                    char c = ((b + f) % 26) + 65;
                    printf("%c", c);
                    j = j + 1;
                    //loops key if key ends before text
                    key[j] = key[(j % m)];


                }
                //print as if when text is not alphabetic
                else if (text[i] != isalpha(text[i]))
                {
                    printf("%c", text[i]);


                }




            }
        }



    }
    else
    {
        printf("Argument entry errror\n");
        return 1;
    }
    printf("\n");
}


