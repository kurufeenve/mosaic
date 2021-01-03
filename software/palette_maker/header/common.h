#ifndef COMMON_H
#define COMMON_H

/* EXTERNAL */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

/* INTERNAL */
#include "../libft/includes/libft.h"

#define B 0
#define G 1
#define R 2
#define A 3

#define FULL_HEADER_SIZE (sizeof(FileHeader) + sizeof(InfoHeader))

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

typedef struct	headers
{
	FileHeader	file_h;
	InfoHeader	info_h;
}				Headers;

typedef union	pixel
{
	uint32_t	color;
	uint8_t		channel[4];
}				Pixel;

typedef struct	palette
{
	char		*folder_name;
	char		**files;
	uint32_t	*colors;
	char		*palette_name;
	char		*lookup_table;
}				Palette;

#endif
