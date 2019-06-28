// Helper functions for music
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <math.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    //subtracting 0 for ASCII index values
    double n = fraction[0] - '0';
    double d = fraction[2] - '0';
    int dur = (n / d) * 8.0;
    return dur;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    //l stores length of array
    int l = strlen(note);
    //formula to shift to next semi-tone
    float fm = pow(2, (1 / 12));

    //reference variables for normal
    float a = 440.0;
    float b = a * pow(fm, 2);
    float c = b * fm;
    float d = c * pow(fm, 2);
    float e = d * pow(fm, 2);
    float f = e * fm;
    float g = f * pow(fm, 2);

    //reference variables for #
    float A = a * fm;
    float B = b * fm;
    float C = c * fm;
    float D = d * fm;
    float E = D * fm;
    float F = E * fm;
    float G = F * fm;

    //reference variables for flat notes
    float Ab = a / fm ;
    float Bb = b / fm;
    float Cb = c / fm;
    float Db = d / fm;
    float Eb = e / fm;
    float Fb = f / fm;
    float Gb = g / fm;


    //p is returned by the function
    int p;
    //loop corresponding to different octaves
    for (int m = 0; m <= 8 ; m++ )
    {
        //following lines for normal notes calculation
        if (l == 1 && note[0] == 'A')
        {
            if ((int)(note[1]) == 4)
            {
                return a;
            }
            //Caculates for different octaves
            else if ((int)(note[1]) == m & (int)(note[1]) < 4)
            {
                p = a / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if ((int)(note[1]) == m & (int)(note[1]) > 4)
            {
                p = roundf(a * pow(2, m - 4));
                return p;
            }
        }
        //calculates for A sharp notes in any octave
        else if (l == 2 && note[1] == '#' && note[0] == 'A')
        {
            if ((int)(note[2]) == 4)
            {
                A = roundf(A);
                return A;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) < 4)
            {
                p = roundf(A / pow(2, 4 - m));
                return p;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) > 4)
            {
                p = A * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }
        //calculates A flat notes for any octave
        else if (l == 2 && note[1] == 'b' && note[0] == 'A')
        {
            if ((int)(note[2]) == 4)
            {
                Ab = roundf(Ab);
                return Ab;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) < 4)
            {
                p = Ab / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) > 4)
            {
                p = Ab * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }
        //Calculates freq for normal B notes in different octaves
        else if (note[0] == 'B')
        {
            if ((int)(note[1]) == 4)
            {
                b = roundf(b);
                return b;
            }
            else if ((int)(note[1]) == m && (int)(note[1]) < 4)
            {
                p = b / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if ((int)(note[1]) == m && (int)(note[1]) > 4)
            {
                p = b * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }//calculates for B sharp notes in any octave
        else if (l == 2 && note[1] == '#' && note[0] == 'B')
        {
            if ((int)(note[2]) == 4)
            {
                B = roundf(B);
                return B;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) < 4)
            {
                p = B / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) > 4)
            {
                p = B * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }
        //calculates freq for B flat
        else if (l == 2 && (int)(note[1]) == 'b' && (int)(note[0]) == 'B')
        {
            if ((int)(note[2]) == 4)
            {
                Bb = roundf(Bb);
                return Bb;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) < 4)
            {
                p = Bb / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if (note[2] == m && note[2] > 4)
            {
                p = Bb * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }
        //Calculates for normal C notes
        else if (note[0] == 'C')
        {
            if ((int)(note[1]) == 4)
            {
                c = roundf(c);
                return c;
            }
            else if ((int)(note[1]) == m && (int)(note[1]) < 4)
            {
                p = c / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if ((int)(note[1]) == m && (int)(note[1]) > 4)
            {
                p = c * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }//calculates for C sharp notes in any octave
        else if (l == 2 && note[1] == '#' && note[0] == 'C')
        {
            if ((int)(note[2]) == 4)
            {
                C = roundf(C);
                return C;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) < 4)
            {
                p = C / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) > 4)
            {
                p = C * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }//Calculates for C flat
        else if (l == 2 && note[1] == 'b' && note[0] == 'C')
        {
            if ((int)(note[2]) == 4)
            {
                Cb = roundf(Cb);
                return Cb;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) < 4)
            {
                p = Cb / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) > 4)
            {
                p = Cb * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }
        //Calculates freq for normal D
        else if (note[0] == 'D')
        {
            if ((int)(note[1]) == 4)
            {
                d = roundf(d);
                return d;
            }
            else if ((int)(note[1]) == m && (int)(note[1]) < 4)
            {
                p = d / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if ((int)(note[1]) == m && (int)(note[1]) > 4)
            {
                p = d * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }//calculates for D sharp notes in any octave
        else if (l == 2 && note[1] == '#' && note[0] == 'D')
        {
            if ((int)(note[2]) == 4)
            {
                D = roundf(d);
                return D;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) < 4)
            {
                p = D / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) > 4)
            {
                p = D * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }//Checks for D flat notes
        else if (l == 2 && note[1] == 'b' && note[0] == 'D')
        {
            if ((int)(note[2]) == 4)
            {
                Db = roundf(Db);
                return Db;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) < 4)
            {
                p = Db / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) > 4)
            {
                p = Db * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }//Calcuates notes for normal E
        else if (note[0] == 'E')
        {
            if ((int)(note[1]) == 4)
            {
                e = roundf(e);
                return e;
            }
            else if ((int)(note[1]) == m && (int)(note[1]) < 4)
            {
                p = e / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if (note[1] == m && note[1] > 4)
            {
                p = e * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }//calculates for E sharp notes in any octave
        else if (l == 2 && note[1] == '#' && note[0] == 'E')
        {
            if ((int)(note[2]) == 4)
            {
                E = roundf(E);
                return E;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) < 4)
            {
                p = E / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) > 4)
            {
                p = E * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }
        //calculates freq for Eb notes in any octave
        else if (l == 2 && note[1] == 'b' && note[0] == 'E')
        {
            if (note[2] == 4)
            {
                Eb = roundf(Eb);
                return Eb;
            }

            else if ((int)(note[2]) == m && (int)(note[2]) < 4)
            {
                p = Eb / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) > 4)
            {
                p = Eb * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }
        //Calculates notes for normal F
        else if (note[0] == 'F')
        {
            if ((int)(note[1]) == 4)
            {
                f = roundf(f);
                return f;
            }
            else if ((int)(note[1]) == m && (int)(note[1]) < 4)
            {
                p = f / pow(2, 4 - m);
                return p;
            }
            else if ((int)(note[1]) == m && (int)(note[1]) > 4)
            {
                p = f * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }//calculates for F sharp notes in any octave
        else if (l == 2 && note[1] == '#' && note[0] == 'F')
        {
            if (note[2] == 4)
            {
                F = roundf(F);
                return F;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) < 4)
            {
                p = F / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) > 4)
            {
                p = F * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }
        //Checks for F flat notes in any octave
        else if (l == 2 && note[1] == 'b' && note[0] == 'F')
        {
            if ((int)(note[2]) == 4)
            {
                Fb = roundf(Fb);
                return Fb;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) < 4)
            {
                p = Fb / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) > 4)
            {
                p = Fb * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }//Checks for normal notes of G
        else if (note[0] == 'G')
        {
            if ((int)(note[1]) == 4)
            {
                g = roundf(g);
                return g;
            }
            else if ((int)(note[1]) == m && (int)(note[1]) < 4)
            {
                p = g / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if ((int)(note[1]) == m && (int)(note[1]) > 4)
            {
                p = g * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }///calculates for G sharp notes in any octave
        else if (l == 2 && note[1] == '#' && note[0] == 'G')
        {
            if ((int)(note[2]) == 4)
            {
                G = roundf(G);
                return G;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) < 4)
            {
                p = G / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if (note[2] == m && note[2] > 4)
            {
                p = G * pow(2, m - 4);
                p = roundf(p);
                return p;
            }
        }
        //Calculates for G flats
        else if (l == 2 && note[1] == 'b' && note[0] == 'G')
        {
            if (note[2] == 4)
            {
                Gb = roundf(Gb);
                return Gb;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) < 4)
            {
                p = Gb / pow(2, 4 - m);
                p = roundf(p);
                return p;
            }
            else if ((int)(note[2]) == m && (int)(note[2]) > 4)
            {
                p = Gb * pow(2, c - 4);
                p = roundf(p);
                return p;
            }
        }

    }
    //return 0 if nothing matches
    return false;
}






// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (s[0] == '\0')
    {
        return true;
    }
    else
    {
        return false;
    }
}
