# Questions

## What's `stdint.h`?

A header file in C that defines the typedef function to allow the user to define custom int data types with user-defined width (length in bits)

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

intN_t is the syntactical shorthand for 'a type of integer of length N bits'. The addition of u in uintN_t defines the type as an unsigned int.
In the context of typedef, intN_t and uintN_t, allow the user to define new int data types of exact width.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE - 8bits
DWORD - 32bits
LONG - 32bits
WORD - 16bits

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

In ASCII, 66 and 77

## What's the difference between `bfSize` and `biSize`?

bfSize is the size of the bitmap file in bytes
biSize is the size of the BITMAPINFOHEADER structure in bytes

## What does it mean if `biHeight` is negative?

There are 2 variations of Device-Independent Bitmaps (DIBs), which are assigned to either a positive or negative biHeight value. 
A negative biHeight value is assigned to the variation that is defined as 'a top-down DIB and its origin is the upper-left corner'.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in `copy.c`?

If NULL is returned, its an indication that the file referenced in fopen did not open successfully. 
A situation in which NULL is returned could be that the computer could not locate the file. 

## Why is the third argument to `fread` always `1` in our code?

Because the the third argument determines the number of elements to be read by fread. In the case of BITMAPFILEHEADER and BITMAPINFOHEADER, there's only one of each in a BMP file so fread is instructed to read it once. However, there are many pixels, each coded by a sequence of 24-bits called RGBTRIPLE so we would have to read multiple instances of RGBTRIPLE to copy a BMP file. But because fread is embedded in a for loop, the third argument is 1. 

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

fseek is a function that changes the address stored in a pointer to a different, user-defined, address.

## What is `SEEK_CUR`?

fseek() changes the address stored in a pointer by adding or subtracting an offset integer from a starting point. In this context, SEEK_CUR tells fseek() to add/subtract the offset value from the where the file pointer is currently pointing to.
