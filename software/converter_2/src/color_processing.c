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
    P->channel[R] = C.data[byte_index + R];
    P->channel[G] = C.data[byte_index + G];
    P->channel[B] = C.data[byte_index + B];
    P->channel[A] = C.data[byte_index + A];
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
    C->data[byte_index + R] = P.channel[R];
    C->data[byte_index + G] = P.channel[G];
    C->data[byte_index + B] = P.channel[B];
    C->data[byte_index + A] = P.channel[A];
}

/******************************************************************************/
/*                                                                            */
/*       returns average of two colors                                        */
/*                                                                            */
/******************************************************************************/

static Pixel	colorAverage(Pixel p1, Pixel p2)
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

/*****************************************************************************/
/*                                                                           */
/*       finding average color                                               */
/*                                                                           */
/*****************************************************************************/

void    tileAverage(Pixel *P, uint8_t *data, uint32_t len)
{
	uint8_t		*buf;
	uint32_t    image_size;
	uint32_t    j;
	Pixel		color;

	image_size = len;
	buf = (uint8_t *)malloc(sizeof(uint8_t) * (image_size / 2));
	while (image_size > 7)
	{
		j = 0;
		for (uint32_t i = 0; i < image_size - 7; i+=8)
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
	free(buf);
    for (uint32_t i = 4; i < len; i+=4)
    {
        data[i + R] = data[R];
        data[i + G] = data[G];
        data[i + B] = data[B];
        data[i + A] = data[A];
    }
}
