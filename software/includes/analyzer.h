#ifndef ANALYZER_H
#define ANALYZER_H

#include "converter.h"
#include <stdlib.h>

/*#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })*/

typedef struct	s_min_max
{
	uint8_t		r_min;
	uint8_t		r_max;
	uint8_t		g_min;
	uint8_t		g_max;
	uint8_t		b_min;
	uint8_t		b_max;
}				t_min_max;

typedef struct	s_color_delta
{
	uint8_t		r_delta;
	uint8_t		g_delta;
	uint8_t		b_delta;
}				t_color_delta;

typedef struct	s_pixels
{
	t_color		*pixels;
	uint32_t	*mem_addrs;
	t_color		*colors;
}				t_pixels;

void	pixel_iterator(uint8_t *data, t_headers headers, void *ptr, void (*f)(void *, void *, void *, void *));
uint8_t	min(uint8_t a, uint8_t b);
uint8_t	max(uint8_t a, uint8_t b);
void	check_pixel(void *bytes, void *mn_mx, void *pxl_nbr, void *head);
void	m_delta_calc(t_min_max min_max, t_color_delta *d);
void	fill_pixels(void *bytes, void *pix, void *pxl_nbr, void *head);
int		median_compare_r(const void *pixel1, const void *pixel2);
void	median_cut(uint8_t *bytes, t_headers headers);

#endif
