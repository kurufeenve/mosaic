#ifndef COLOR_PROCESSING_H
#define COLOR_PROCESSING_H

#include "common.h"
#include "color_comparison.h"

void    getPixel(Pixel *P, Converter C, uint32_t x, uint32_t y);
void    setPixel(Pixel P, Converter *C, uint32_t x, uint32_t y);
Pixel	colorAverage(Pixel p1, Pixel p2);
void    getPaletteColor(void *color, Palette Pal);

#endif
