# Questions

## What's `stdint.h`?

The library of typedefs which Microsoft uses for datatypes in BMP to make variables of whatever size Microsoft needs

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

It assigns bytes attributed to each file in order to use as much space as needed for each file

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE = 1 byte
DWORD4 = 4 bytes
LONG = 4 bytes
WORD = 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

0x424d

## What's the difference between `bfSize` and `biSize`?

bfSize is the number of bytes in the file whereas biSize is the number of bytes in the infoheader

## What does it mean if `biHeight` is negative?

If biHeight is negative, the first byte in memory is the top-left pixel of the image. So the top row of the image is the first row in memory, followed by the next row down.


## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

If it is unable to find the file it is supposed to open

## Why is the third argument to `fread` always `1` in our code?

The one refers to the number of elements being read which in this case is a unique struct

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

It goes to a certain location in the file

## What is `SEEK_CUR`?

Seek_CUR as an argument in fseek specifies that the offset provided is relative to the position of the current file.
