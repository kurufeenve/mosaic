#include "./includes/converter.h"

void	print_bytes(uint8_t *bytes, size_t len)
{
	for(size_t i = 0; i < len; i++)
	{
		printf("%02x ", bytes[i]);
		if (!(i % 16) && i != 0)
		{
			printf("\n");
		}
	}
	printf("\n");
}

void	put_pixel(uint8_t *data, t_color color, t_coords coords, t_headers headers)
{
	size_t	pixel_number;

	if (headers.image_header.biBitCount == 32)
	{
		pixel_number = headers.file_header.bfOffBits + (coords.y * headers.image_header.biWidth + coords.x) * 4;
		data[pixel_number + RESERVED] = color.channel[RESERVED];
		data[pixel_number + RED] = color.channel[RED];
		data[pixel_number + GREEN] = color.channel[GREEN];
		data[pixel_number + BLUE] = color.channel[BLUE];
	}
}

void	image_processing(uint8_t *bytes, t_headers headers)
{
	t_coords	coords;
	t_color		color;

	color.color = 0xff55c5cf;
	for (int i = 0; i < headers.image_header.biHeight; i++)
	{
		for (int j = 0; j < headers.image_header.biWidth; j++)
		{
			coords.x = j;
			coords.y = i;
			put_pixel(bytes, color, coords, headers);
		}
	}
}
