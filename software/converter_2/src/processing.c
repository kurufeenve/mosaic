#include "processing.h"


/******************************************************************************/
/*                                                                            */
/*       paint the space between the tiles                                    */
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
                setPixel(C->mesh_color, C, x, y);
            }
            else if (x % 11 == 0)
            {
                setPixel(C->mesh_color, C, x, y);
            }
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
    readPalette(C);
    iterateTile(C);
    writeBMP("test_img/processed_image.bmp", *C);
}
