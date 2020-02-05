#include "includes/analyzer.h"

void	bytes_to_pixels(uint8_t *data, t_headers headers, t_color *pixels)
{
	size_t	byte_number;
	size_t	pixel_number

	for (int i = 0; i < headers.image_header.biHeight; i++)
	{
		for (int j = 0; j < headers.image_header.biWidth; j++)
		{
			byte_number = headers.file_header.bfOffBits + (i * \
headers.image_header.biWidth + j) * headers.image_header.biBitCount / 8;
			pixel_number = i * j;
			pixels[pixel_number].channel[RED] = data[byte_number + RED];
			pixels[pixel_number].channel[GREEN] = data[byte_number + GREEN];
			pixels[pixel_number].channel[BLUE] = data[byte_number +BLUE];
			if (headers.image_header.biBitCount == 32)
			{
				pixels[pixel_number].channel[RESERVED] = data[byte_number + RESERVED];
			}
		}
	}
}

void	pixels_to_bytes(uint8_t *data, t_headers headers, t_color *pixels)
{
	size_t	byte_number;
	size_t	pixel_number

	for (int i = 0; i < headers.image_header.biHeight; i++)
	{
		for (int j = 0; j < headers.image_header.biWidth; j++)
		{
			byte_number = headers.file_header.bfOffBits + (i * \
headers.image_header.biWidth + j) * headers.image_header.biBitCount / 8;
			pixel_number = i * j;
			data[byte_number + RED] = pixels[pixel_number].channel[RED];
			data[byte_number + GREEN] = pixels[pixel_number].channel[GREEN];
			data[byte_number +BLUE] = pixels[pixel_number].channel[BLUE];
			if (headers.image_header.biBitCount == 32)
			{
				data[byte_number + RESERVED] = pixels[pixel_number].channel[RESERVED];
			}
		}
	}
}

void	pixel_iterator(t_color *pixels, size_t pixels_total, void *ptr, void (*f)(void *, void *, void *, void *))
{
	for (int i = 0; i < pixels_total; i++)
	{
		f((void *)pixels, ptr, (void *)&pixel_number, NULL);
	}
}

void	analyzer(uint8_t *bytes, t_headers headers)
{
	t_color		*pixels;
	size_t		total_pixels;

	total_pixels = headers.image_header.biHeight * headers.image_header.biWidth;
	pixels = (t_color *)malloc(sizeof(t_color) * total_pixels);
	memset(pixels, 0, total_pixels);
	pixel_iterator(bytes, headers, (void *)pixels, fill_pixels);
}
