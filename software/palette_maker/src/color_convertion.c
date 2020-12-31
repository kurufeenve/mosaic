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
	int			image_size;

	printf("filename = %s\n", file_name);
	readFile(file_name, (uint8_t *)&headers, &data);

	image_size = headers.file_h.bfSize - headers.file_h.bfOffBits;
	/*for (int i = headers.file_h.bfOffBits; i < image_size; i+=4)
	{
		printf("%08x\n", *(uint32_t *)(&data[i]));
	}*/
	free(data);
}

/********************************************/
/*                                          */
/*  creates pallete and writes it			*/
/*  to the file							 	*/
/*                                          */
/********************************************/
void	converter(Palette *P)
{
	char	hex_test[] = "0x00000000";

	fileToHex(P->files[0], hex_test);
	printf("hex = %s\n", hex_test);
}
