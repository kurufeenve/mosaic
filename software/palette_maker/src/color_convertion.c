#include "color_convertion.h"

/********************************************/
/*                                          */
/*  returns average of two colors           */
/*                                          */
/********************************************/

Pixel	colorAverage(Pixel p1, Pixel p2)
{
	Pixel		avg;

	avg.channel[R] = sqrt((p1.channel[R] * p1.channel[R] +
		p2.channel[R] * p2.channel[R]) / 2);
	avg.channel[G] = sqrt((p1.channel[G] * p1.channel[G] +
		p2.channel[G] * p2.channel[G]) / 2);
	avg.channel[B] = sqrt((p1.channel[B] * p1.channel[B] +
		p2.channel[B] * p2.channel[B]) / 2);
	avg.channel[A] = sqrt((p1.channel[A] * p1.channel[A] +
		p2.channel[A] * p2.channel[A]) / 2);
	return (avg);
}

/********************************************/
/*                                          */
/*  get hex numbers from textures           */
/*                                          */
/********************************************/
void	fileToHex(char *file_name, char *hex)
{
	Headers		headers;
	uint8_t		*data;
	uint8_t		*buf;
	int		image_size;
	int		j;
	Pixel		color;
	char		*midle;

	printf("filename = %s\n", file_name);
	readFile(file_name, (uint8_t *)&headers, &data);

	image_size = headers.file_h.bfSize - headers.file_h.bfOffBits;
	buf = (uint8_t *)malloc(sizeof(uint8_t) * (image_size / 2));
	while (image_size > 7)
	{
		j = 0;
		for (int i = 0; i < image_size - 7; i+=8)
		{
			color = colorAverage(*((Pixel *)(&(data[i]))),
					*((Pixel *)(&(data[i + 4]))));
			ft_memcpy((void *)(&(buf[j])),
				(void *)(&(color.color)), 4);
			j += 4;
		}
		ft_bzero(data, image_size);
		image_size /= 2;
		memcpy((void *)data, (void *)buf, image_size);
		ft_bzero(buf, image_size);
	}
	j = 0;
	for (int i = 0; i < 4; i++)
	{
		memcpy((void *)&hex[j], ft_itoa_base(data[i], 16), 2);
		j += 2;
	}
	printf("hex = %s\n", hex);
	free(buf);
	free(data);
}

/********************************************/
/*                                          */
/*  creates pallete and writes it           */
/*  to the file                             */
/*                                          */
/********************************************/
void	converter(Palette *P)
{
	char	hex_test[9];

	ft_bzero(hex_test, 9);
	fileToHex(P->files[0], hex_test);
	printf("hex = %s\n", hex_test);
}
