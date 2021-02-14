#include "color_processing.h"

/*****************************************************************************/
/*                                                                           */
/*       getting pixel from coordinates                                      */
/*                                                                           */
/*****************************************************************************/

void    getPixel(Pixel *P, Converter C, uint32_t x, uint32_t y)
{
    uint32_t    byte_index;

    byte_index = y * C.headers.info_h.biWidth * 4 + x * 4;
    P->color = *(uint32_t *)&C.data[byte_index];
    /*P->channel[R] = C.data[byte_index + R];
    P->channel[G] = C.data[byte_index + G];
    P->channel[B] = C.data[byte_index + B];
    P->channel[A] = C.data[byte_index + A];*/
}

/*****************************************************************************/
/*                                                                           */
/*       setting pixel in coordinates                                        */
/*                                                                           */
/*****************************************************************************/

void    setPixel(Pixel P, Converter *C, uint32_t x, uint32_t y)
{
    uint32_t    byte_index;

    byte_index = y * C->headers.info_h.biWidth * 4 + x * 4;
    *(uint32_t *)&C->data[byte_index] = P.color;
    /*C->data[byte_index + R] = P.channel[R];
    C->data[byte_index + G] = P.channel[G];
    C->data[byte_index + B] = P.channel[B];
    C->data[byte_index + A] = P.channel[A];*/
}

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

void    getPaletteColor(void *color, Palette Pal)
{
    uint64_t    dif[2];
    uint32_t    color_number;

    dif[1] = -1;
    for (uint32_t i = 0; i < Pal.palette_size; i++)
    {
        dif[0] = matchColorEuclidean(color, (void *)&Pal.palette[i].color);
        if (dif[0] < dif[1])
        {
            dif[1] = dif[0];
            color_number = i;
        }
    }
    memcpy(color, (void *)&Pal.palette[color_number].color, 4);
}
