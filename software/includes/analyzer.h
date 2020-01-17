#ifndef ANALYZER_H
#define ANALYZER_H

#include "include/converter.h"

typedef struct	s_min_max
{
	uint8_t	r_min;
	uint8_t	r_max;
	uint8_t	g_min;
	uint8_t	g_max;
	uint8_t	b_min;
	uint8_t	b_max;
}		t_min_max;

void	check_pixel(uint8_t *data, t_headers headers);

#endif
