#ifndef ANALYZER_H
#define ANALYZER_H

#include "converter.h"
#include <stdlib.h>

void	bytes_to_pixels(uint8_t *data, t_headers headers, t_color *pixels);
void	pixels_to_bytes(uint8_t *data, t_headers headers, t_color *pixels);

void	pixel_iterator(t_color *pixels, size_t pixels_total, \
void *ptr, void (*f)(void *, void *, void *, void *));

void	analyzer(uint8_t *bytes, t_headers headers);

#endif
