#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#define Buff 512

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    unsigned char buffer[Buff];

    //open memory card file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fclose(file);
        fprintf(stderr, "Error opening card.raw\n");
        return 1;
    }


    //counter for files
    int filecount = 0;

    FILE *image = NULL;

    //keeps track of files found
    int oncounter = 0;



    while (fread(buffer, 512, 1, file) == 1)
    {
        //read 4 bytes of buffer to check for jpg signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer [3] & 0xf0) == 0xe0)

        {

            //start of new image to be recovered found
            if (oncounter == 1)
            {

                fclose(image);


            }

            char name[8];
            sprintf(name, "%03i.jpg", filecount);

            //first jpg image found
            image = fopen(name, "w");
            fwrite(buffer, Buff, 1, image);
            filecount = filecount + 1;
            oncounter = 1;




        }
        else if (oncounter == 1)
        {
            fwrite(buffer, Buff, 1, image);
        }
    }
    fclose(file);
    fclose(image);
    return 0;

}
