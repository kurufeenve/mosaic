#include "tile_processing.h"

/******************************************************************************/
/*                                                                            */
/*       reads tile into a bufer                                              */
/*                                                                            */
/******************************************************************************/

static uint8_t *readTile(Converter *C, uint32_t x_start, uint32_t y_start)
{
    uint8_t     *buf;
    uint32_t    buf_it;
    uint32_t    y_end = y_start + TILE_SIZE;

    buf = (uint8_t *)malloc(sizeof(uint8_t) * TILE_SIZE * TILE_SIZE * 4);
    buf_it = 0;
    for (uint32_t y = y_start; y < y_end; y++)
    {
        ft_memcpy((void *)&buf[buf_it],
            (void *)&C->data[y * C->headers.info_h.biWidth * 4 + x_start * 4],
            TILE_SIZE * 4);
        buf_it += (TILE_SIZE * 4);
    }
    return (buf);
}

/******************************************************************************/
/*                                                                            */
/*       write color to a tile coordinates                                    */
/*                                                                            */
/******************************************************************************/

static void    writeTile(Converter *C, uint32_t x_start, uint32_t y_start,
        Pixel P)
{
    uint32_t    x_end = x_start + TILE_SIZE;
    uint32_t    y_end = y_start + TILE_SIZE;

    for (uint32_t y = y_start; y < y_end; y++)
    {
        for (uint32_t x = x_start; x < x_end; x++)
        {
            *(uint32_t *)&C->data[y * C->headers.info_h.biWidth * 4
                + x * 4] = P.color;
        }
    }
}

/*****************************************************************************/
/*                                                                           */
/*       finding average color                                               */
/*                                                                           */
/*****************************************************************************/

static void    tileAverage(uint8_t *data, uint32_t len)
{
	uint8_t		*buf;
	uint32_t    image_size;
	uint32_t    j;
    Pixel       P;

	image_size = len;
	buf = (uint8_t *)malloc(sizeof(uint8_t) * (image_size / 2));
	while (image_size > 7)
	{
		j = 0;
		for (uint32_t i = 0; i < image_size - 7; i+=8)
		{
			P = colorAverage(*((Pixel *)(&(data[i]))),
					*((Pixel *)(&(data[i + 4]))));
			ft_memcpy((void *)(&(buf[j])), (void *)(&(P.color)), 4);
			j += 4;
		}
		ft_bzero(data, image_size);
		image_size /= 2;
		memcpy((void *)data, (void *)buf, image_size);
		ft_bzero(buf, image_size);
	}
	free(buf);
}

/******************************************************************************/
/*                                                                            */
/*       processes single tile by finding average color                       */
/*       of the tile then comparing it with palette and                       */
/*       finding most similar color in the palette and                        */
/*       writing it back to the tile                                          */
/*                                                                            */
/******************************************************************************/

static void    processTile(Converter *C, uint32_t x_start, uint32_t y_start)
{
    uint8_t     *buf;

    buf = readTile(C, x_start, y_start);
    tileAverage(buf, (TILE_SIZE * TILE_SIZE * 4));
    getPaletteColor((void *)buf, C->palette);
    writeTile(C, x_start, y_start, *(Pixel *)buf);
    free(buf);
}

/******************************************************************************/
/*                                                                            */
/*       iterates through tiles' first pixel coordinates                      */
/*                                                                            */
/******************************************************************************/

void    iterateTile(Converter *C)
{
    for (int y = 1; y < C->headers.info_h.biHeight; y+=11)
    {
        for (int x = 1; x < C->headers.info_h.biWidth; x+=11)
        {
            processTile(C, x, y);
        }
    }
}
