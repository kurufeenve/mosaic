#include "processing.h"

/*****************************************************************************/
/*                                                                           */
/*       setting pixel in coordinates                                        */
/*                                                                           */
/*****************************************************************************/

void    putPixel(Pixel P, Converter *C, uint32_t x, uint32_t y)
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

static void    processTile(uint8_t *data, x_start, y_start)
{

}

static void    iterateTile(Converter *C)
{
    for (y = 1; y < C->headers.info_h.biHeight; y+=11)
    {
        for (int x = 1; x < C->headers.info_h.biWidth; x+=11)
        {

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
    writeBMP("test_img/processed_image.bmp", *C);
}
