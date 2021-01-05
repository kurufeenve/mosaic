#include "color_convertion.h"

/******************************************************************************/
/*                                                                            */
/*       returns average of two colors                                        */
/*                                                                            */
/******************************************************************************/

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

/******************************************************************************/
/*       convert uint to string in                                            */
/*       hex format                                                           */
/*                                                                            */
/******************************************************************************/

void	uintToString(uint8_t *color, char *string)
{
	char	*buf;
	int	j;
	size_t	buf_len;

	j = 0;
	for (int i = 0; i < 4; i++)
	{
		buf = ft_itoa_base(color[i], 16);
		buf_len = ft_strlen(buf);
		if (buf_len < 2)
		{
			j++;
		}
		memcpy((void *)&string[j], buf, buf_len);
		free(buf);
		if (buf_len < 2)
		{
			j++;
		}
		else
		{
			j += 2;
		}
	}
}

/******************************************************************************/
/*                                                                            */
/*       get hex numbers from textures                                        */
/*                                                                            */
/******************************************************************************/

void	fileToHex(char *file_name, char *hex)
{
	Headers		headers;
	uint8_t		*data;
	uint8_t		*buf;
	int		image_size;
	int		j;
	Pixel		color;

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
	uintToString(data, hex);
	free(buf);
	free(data);
}

/******************************************************************************/
/*                                                                            */
/*       creates pallete and writes it                                        */
/*       to the file                                                          */
/*                                                                            */
/******************************************************************************/

void	converter(Palette *P)
{
	char	*palette;

	palette = ft_strnew(P->files_num * COLOR_LEN);
	//ft_bzero(palette, (P->files_num * COLOR_LEN));
	for (uint16_t i = 0; i < P->files_num; i++)
	{
		ft_memset((void *)&palette[i * COLOR_LEN], '0', 8);
		fileToHex(P->files[i], &palette[i * COLOR_LEN]);
		palette[i * COLOR_LEN + COLOR_LEN - 1] = '\n';
	}
	writeFile(P->palette_name, palette);
	free(palette);
}
