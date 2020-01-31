#include "includes/analyzer.h"

void	bytes_to_pixels(uint8_t *data, t_headers headers, t_)
{
	
}

void	pixel_iterator(uint8_t *data, t_headers headers, void *ptr, void (*f)(void *, void *, void *, void *))
{
	size_t	pixel_number;

	for (int i = 0; i < headers.image_header.biHeight; i++)
	{
		for (int j = 0; j < headers.image_header.biWidth; j++)
		{
			pixel_number = headers.file_header.bfOffBits + (i * \
headers.image_header.biWidth + j) * headers.image_header.biBitCount / 8;
			f((void *)data, ptr, (void *)&pixel_number, (void *)&headers);
		}
	}
}

uint8_t	min(uint8_t a, uint8_t b)
{
	if (a < b)
	{
		return (a);
	}
	else
	{
		return (b);
	}
}

uint8_t	max(uint8_t a, uint8_t b)
{
	if (a > b)
	{
		return (a);
	}
	else
	{
		return (b);
	}
}

void	check_pixel(void *bytes, void *mn_mx, void *pxl_nbr, void *head)
{
	uint8_t 	*data;
	size_t		*pixel_number;
	t_min_max	*min_max;
	t_headers	*headers;

	data = (uint8_t *)bytes;
	pixel_number = (size_t *)pxl_nbr;
	memset(mn_mx, 0, sizeof(t_min_max));
	min_max = (t_min_max *)mn_mx;
	headers = (t_headers *)head;
	if (headers->image_header.biBitCount == 32)
	{
		min_max->r_min = min(data[*pixel_number + RED], min_max->r_min);
		min_max->r_max = max(data[*pixel_number + RED], min_max->r_max);
		min_max->g_min = min(data[*pixel_number + GREEN], min_max->g_min);
		min_max->g_max = max(data[*pixel_number + GREEN], min_max->g_max);
		min_max->b_min = min(data[*pixel_number + BLUE], min_max->b_min);
		min_max->b_max = max(data[*pixel_number + BLUE], min_max->b_max);
	}
}

void	m_delta_calc(t_min_max min_max, t_color_delta *d)
{
	d->r_delta = min_max.r_max - min_max.r_min;
	d->g_delta = min_max.g_max - min_max.g_min;
	d->b_delta = min_max.b_max - min_max.b_min;
}

void	fill_pixels(void *bytes, void *pix, void *pxl_nbr, void *head)
{
	uint8_t 	*data;
	size_t		*pixel_number;
	t_color		*pixels;
	t_headers	*headers;
	size_t		pixel_index;

	data = (uint8_t *)bytes;
	pixel_number = (size_t *)pxl_nbr;
	pixels = (t_color *)pix;
	headers = (t_headers *)head;
	pixel_index = (*pixel_number - headers->file_header.bfOffBits) / 4;
	pixels[pixel_index].channel[RED] = data[*pixel_number + RED];
	pixels[pixel_index].channel[GREEN] = data[*pixel_number + GREEN];
	pixels[pixel_index].channel[BLUE] = data[*pixel_number + BLUE];
	pixels[pixel_index].channel[RESERVED] = data[*pixel_number + RESERVED];
}

int		median_compare_r(const void *pixel1, const void *pixel2)
{
	t_color	*p1;
	t_color *p2;

	p1 = (t_color *)pixel1;
	p2 = (t_color *)pixel2;
	if (p1->channel[RED] == p2->channel[RED])
	{
		if (p1->channel[GREEN] == p2->channel[GREEN])
		{
			return (int)p1->channel[BLUE] - (int)p2->channel[BLUE];
		}
		return (int)p1->channel[GREEN] - (int)p2->channel[GREEN];
	}
	return (int)p1->channel[RED] - (int)p2->channel[RED];
}

void	median_cut(uint8_t *bytes, t_headers headers)
{
	t_min_max	min_max;
	t_color		*pixels;
	size_t		total_pixels;

	total_pixels = headers.image_header.biHeight * headers.image_header.biWidth;
	memset(&min_max, 0, sizeof(min_max));
	min_max.r_min = 255;
	min_max.g_min = 255;
	min_max.b_min = 255;
	pixel_iterator(bytes, headers, (void *)&min_max, &check_pixel);
	pixels = (t_color *)malloc(sizeof(t_color) * total_pixels);
	memset(pixels, 0, total_pixels);
	pixel_iterator(bytes, headers, (void *)pixels, fill_pixels);
}
