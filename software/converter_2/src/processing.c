#include "processing.h"

/*****************************************************************************/
/*                                                                           */
/*       getting pixel from coordinates                                      */
/*                                                                           */
/*****************************************************************************/

static void    getPixel(Pixel *P, Converter C, uint32_t x, uint32_t y)
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

static void    putPixel(Pixel P, Converter *C, uint32_t x, uint32_t y)
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
/*       color the space between the tiles                                    */
/*                                                                            */
/******************************************************************************/

static void    meshColoring(Converter *C)
{
    for (int y = 0; y < C->headers.info_h.biHeight; y++)
    {
        for (int x = 0; x < C->headers.info_h.biWidth; x++)
        {
            if (y % 11 == 0)
            {
                putPixel(C->mesh_color, C, x, y);
            }
            else if (x % 11 == 0)
            {
                putPixel(C->mesh_color, C, x, y);
            }
        }
    }
}

static void    processTile(Converter *C, uint32_t x_start, uint32_t y_start)
{
    Pixel       P;
    uint8_t     *buf;
    uint32_t    buf_it;
    //uint32_t    x_end = x_start + TILE_SIZE;
    uint32_t    y_end = y_start + TILE_SIZE;

    P.color = 0x0000ffff;
    buf = (uint8_t *)malloc(sizeof(uint8_t) * TILE_SIZE * TILE_SIZE * 4);
    buf_it = 0;
    for (uint32_t y = y_start; y < y_end; y++)
    {
        /*for (uint32_t x = x_start; x < x_end; x++)
        {
            putPixel(P, C, x, y);
        }*/
        ft_memcpy((void *)&buf[buf_it],
            (void *)&C->data[y * C->headers.info_h.biWidth * 4 + x_start * 4],
            TILE_SIZE * 4);
        buf_it += (TILE_SIZE * 4);
    }
    free(buf);
}

/******************************************************************************/
/*                                                                            */
/*       iterates through tiles' first pixel coordinates                      */
/*                                                                            */
/******************************************************************************/

static void    iterateTile(Converter *C)
{
    for (int y = 1; y < C->headers.info_h.biHeight; y+=11)
    {
        for (int x = 1; x < C->headers.info_h.biWidth; x+=11)
        {
            processTile(C, x, y);
        }
    }
}

/******************************************************************************/
/*                                                                            */
/*       processes the image by calling more basic functions                  */
/*                                                                            */
/******************************************************************************/

void    processing(Converter *C)
{
    readBMP(C->img_name, (uint8_t *)&C->headers, &C->data);
    if (C->headers.info_h.biBitCount != 32)
    {
        collect_garbage(C);
        perror("bit count is not suitable. should be 32");
		exit(EXIT_FAILURE);
    }
    meshColoring(C);
    iterateTile(C);
    writeBMP("test_img/processed_image.bmp", *C);
}
