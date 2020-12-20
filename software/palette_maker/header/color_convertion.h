#ifndef COLOR_CONV_H
#define COLOR_CONV_H

#include "common.h"
#include "file_io.h"

Pixel	colorAverage(Pixel p1, Pixel p2);
void	converter(Palette *P);
void	fileToHex(char *file_name, char *hex);

#endif
