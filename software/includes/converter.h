#ifndef CONVERTER_H
#define CONVERTER_H

#include <stdio.h>
#include <stdint.h>

#include "file_io.h"

typedef	union	u_color
{
	uint32_t	color;
	uint8_t		channel[4];
}				t_color;

typedef struct	s_coords
{
	int32_t		x;
	int32_t		y;
}				t_coords;

enum			e_chanels
{
	
	RESERVED,
	RED,
	GREEN,
	BLUE
};

void    print_bytes(uint8_t *bytes, size_t len);
void	put_pixel(uint8_t *data, t_color color, t_coords coords, t_headers headers);
void	image_processing(uint8_t *bytes, t_headers headers);

#endif
