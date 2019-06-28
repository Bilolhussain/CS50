# Emoji

## Questions

1. 2.5 bytes

2. Char always has size 1 meaning 8 bits can be used in the representation. However, for the jack-o-lantern at least 2.5 bytes are
   needed as such it cannot be stored in char.

3.

```c
#include <cs50.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <ctype.h>

typedef wchar_t emoji;
emoji get_emoji(string prompt);
int main(void)
{
    // Set locale according to environment variables
    setlocale(LC_ALL, "");

    // Prompt user for code point
    emoji c = get_emoji("Code point: ");

    // Print character
    printf("%lc\n", c);
}

emoji get_emoji(string prompt)
{

    printf("%s", prompt);
    string d = get_string();
    while (d[0] != 'U' && d[1] != '+')
    {
        printf("%s", prompt);
        d = get_string();
    }

    int length = strlen(d);
    for(int i = 2; i < length; i++)
    {
        //check whether the input is correct
        if ((d[i] < 48 || d[i] > 57) && (d[i] < 65 || d[i] > 70))
            {
                printf("%s", prompt);
                d = get_string();
            }
        else
            {
                break;
            }

    }
    return (strtol(d + 2, NULL, 16));


}
```

## Debrief

1. http://www.asciitable.com/
   https://www.tutorialspoint.com/c_standard_library/c_function_strtol.htm

2. 5 hours
