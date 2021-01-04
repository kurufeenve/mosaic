#ifndef COLOR_CONV_H
#define COLOR_CONV_H

#include "common.h"
#include "file_io.h"

/* 
 * length in bytes of the ascii string for the hex representation of a RGBA color
 * + one byte for \0 or \n symbols
 */
#define COLOR_LEN 9

Pixel	colorAverage(Pixel p1, Pixel p2);
void	converter(Palette *P);
void	fileToHex(char *file_name, char *hex);
void	uintToString(uint8_t *color, char *string);

#endif
