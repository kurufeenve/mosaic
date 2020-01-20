#include "includes/analyzer.h"

void	pixel_iterator(uint8_t *data, t_headers headers, void *ptr, void (*f)(void *, void *, void *, void *))
{
	size_t	pixel_number;

	for (int i = 0; i < headers.image_header.biHeight; i++)
	{
		for (int j = 0; j < headers.image_header.biWidth; j++)
		{
			pixel_number = headers.file_header.bfOffBits + (i * \
headers.image_header.biWidth + j) * headers.image_header.biBitCount / 8;
			f((void *)data, ptr, (void *)&pixel_number, NULL);
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

	data = (uint8_t *)bytes;
	pixel_number = (size_t *)pxl_nbr;
	memset(mn_mx, 0, sizeof(t_min_max));
	min_max = (t_min_max *)mn_mx;
	if (headers.image_header.biBitCount == 32)
	{
		*min_max.r_min = min(data[pixel_number + RED], *min_max.r_min);
		*min_max.r_max = max(data[pixel_number + RED], *min_max.r_max);
		*min_max.r_min = min(data[pixel_number + GREEN], *min_max.r_min);
		*min_max.r_max = max(data[pixel_number + GREEN], *min_max.r_max);
		*min_max.r_min = min(data[pixel_number + BLUE], *min_max.r_min);
		*min_max.r_max = max(data[pixel_number + BLUE], *min_max.r_max);
	}
}

void	madian_cut(uint8_t *bytes, t_headers headers)
{
	t_min_max	min_max;

	pixel_iterator(bytes, headers, (void *)&min_max, &check_pixel);
}
