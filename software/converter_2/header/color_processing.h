#ifndef COLOR_PROCESSING_H
#define COLOR_PROCESSING_H

#include "common.h"

void    getPixel(Pixel *P, Converter C, uint32_t x, uint32_t y);
void    setPixel(Pixel P, Converter *C, uint32_t x, uint32_t y);
void    tileAverage(Pixel *P, uint8_t *data, uint32_t len);

#endif
