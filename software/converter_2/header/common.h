#ifndef COMMON_H
#define COMMON_H

/* EXTERNAL */
#include <stdlib.h>
#include <stdio.h>

/* INTERNAL */
#include "../libft/includes/libft.h"

#define B 0
#define G 1
#define R 2
#define A 3

#define X 0
#define Y 1

#define FULL_HEADER_SIZE (sizeof(FileHeader) + sizeof(InfoHeader) + sizeof(ColorHeader))

typedef struct	tagBITMAPFILEHEADER
{
    uint16_t	bfType;
    uint32_t	bfSize;
    uint16_t	bfReserved1;
    uint16_t	bfReserved2;
    uint32_t	bfOffBits;
} __attribute__((__packed__)) FileHeader;

typedef struct	tagBITMAPINFOHEADER
{
	uint32_t	biSize;
	int32_t		biWidth;
	int32_t		biHeight;
	uint16_t	biPlanes;
	uint16_t	biBitCount;
	uint32_t	biCompression;
	uint32_t	biSizeImage;
	int32_t		biXPelsPerMeter;
	int32_t		biYPelsPerMeter;
	uint32_t	biClrUsed;
	uint32_t	biClrImportant;
} __attribute__((__packed__)) InfoHeader;

typedef struct  BMPColorHeader
{
    uint32_t    red_mask;
    uint32_t    green_mask;
    uint32_t    blue_mask;
    uint32_t    alpha_mask;
    uint32_t    color_space_type;
    uint32_t    unused[16];
} __attribute__((__packed__)) ColorHeader;

typedef struct	headers
{
	FileHeader	file_h;
	InfoHeader	info_h;
    ColorHeader color_h;
}				Headers;

typedef union	pixel
{
	uint32_t	color;
	uint8_t		channel[4];
}				Pixel;

typedef struct  converter
{
    char        *img_name;
    Headers     headers;
    uint8_t     *original_palette;
    uint8_t     *data;
    uint32_t    phys_size[2]; /*physical size where 0 is x and 1 is y*/
    Pixel       mesh_color;
}               Converter;

#endif
