#include "include/analyzer.h"

void	pixel_iterator(uint8_t *data, t_headers headers, (void)(*f)(void *, void *, void *, void *))
{
	for (int i = 0; i < headers.image_header.biHeight; i++)
	{
		for (int j = 0; j < headers.image_header.biWidth; j++)
		{
			coords.x = j;
			coords.y = i;
			f((void *)data, (void *)&color, (void *)&coords, (void *)&headers);
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

void	check_pixel(void *bytes, void *min_max, void *coor, void *head)
{
	uint8_t 	*data;
	size_t		pixel_number;
	t_coords	coords;
	t_headers	headers;

	data = (uint8_t *)bytes;
	coords = (t_coords)*coor;
	headers = (t_headers)*head;
	memset(min_max, 0, sizeof(t_min_max));
	if (headers.image_header.biBitCount == 32)
	{
		pixel_number = headers.file_header.bfOffBits + (coords.y * headers.image_header.biWidth + coords.x) * 4;
		min_max->r_min = min(data[pixel_number + RED], min_max->r_min);
		min_max->r_max = max(data[pixel_number + RED], min_max->r_max);
		min_max->r_min = min(data[pixel_number + GREEN], min_max->r_min);
		min_max->r_max = max(data[pixel_number + GREEN], min_max->r_max);
		min_max->r_min = min(data[pixel_number + BLUE], min_max->r_min);
		min_max->r_max = max(data[pixel_number + BLUE], min_max->r_max);
	}
}
