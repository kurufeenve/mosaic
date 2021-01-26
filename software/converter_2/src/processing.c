#include "processing.h"

void    putPixel(Pixel P, uint8_t *data, uint32_t x, uint32_t y)
{
    
}

/******************************************************************************/
/*                                                                            */
/*       processes the image by calling more basic functions                  */
/*                                                                            */
/******************************************************************************/

void    processing(Converter *C)
{
    Headers H;
    uint8_t *data;

    if (readBMP(C->img_name, (uint8_t *)&H, &data)
            || H.info_h.biBitCount != 32)
    {
        collect_garbage(C);
		exit(EXIT_FAILURE);
    }
    free(data);
}
