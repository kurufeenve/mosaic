#ifndef CONVERTER_H
#define CONVERTER_H

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //for testing

#include "../libft/includes/libft.h"
#include "palette_maker.h"

typedef struct tagBITMAPFILEHEADER
{
    uint16_t     bfType;
    uint32_t     bfSize;
    uint16_t     bfReserved1;
    uint16_t     bfReserved2;
    uint32_t     bfOffBits;
} __attribute__((__packed__)) FileHeader;

typedef struct tagBITMAPINFOHEADER
{
	uint32_t     biSize;
	int32_t      biWidth;
	int32_t      biHeight;
	uint16_t     biPlanes;
	uint16_t     biBitCount;
	uint32_t     biCompression;
	uint32_t     biSizeImage;
	int32_t      biXPelsPerMeter;
	int32_t      biYPelsPerMeter;
	uint32_t     biClrUsed;
	uint32_t     biClrImportant;
} __attribute__((__packed__)) InfoHeader;

typedef struct	Headers
{
	FileHeader	File_Header;
	InfoHeader	Image_Header;
}				Headers_T;

typedef	union	Pixel
{
	uint32_t	color;
	uint8_t		chanel[4];
}				Pixel_T;

typedef struct	Coord
{
	uint32_t	x;
	uint32_t	y;
}				Coord_T;

typedef	struct	Palette
{
	Pixel_T		*Pixel;
	uint32_t	size;
}				Palette_T;

typedef struct	Tile
{
	Coord_T		Real_Coord;
	uint64_t	red;
	uint64_t	green;
	uint64_t	blue;
	Pixel_T		Tile_Color;
}				Tile_T;

typedef struct	Tiles
{
	uint32_t	pixels_per_mm_x;
	uint32_t	pixels_per_mm_y;
	uint32_t	tiles_height;
	uint32_t	tiles_width;
	uint32_t	tiles_number;
	uint64_t	red;
	uint64_t	green;
	uint64_t	blue;
	uint64_t	alpha;
	Pixel_T		Tile_Color;
	Tile_T		*Tiles;
}				Tiles_T;

typedef struct	Speed
{
	double		start;
	double		end;
}				Speed_T; //for testing

typedef	struct	Mosaic
{
	uint32_t	height; //physical height in mm
	uint32_t	width; //physical width in mm
	Headers_T	Headers;
	uint8_t		*image;
	Tiles_T		Tiles;
	Pixel_T		Mesh_Color;
	char		*palette_name;
	Palette_T	Palette;
	Speed_T		Speed; //for testing
}				Mosaic_T;

#define TIME_DIFF(x,y) ((y - x) / CLOCKS_PER_SEC) //for testing

#define FULL_HEADER_SIZE (sizeof(FileHeader) + sizeof(InfoHeader))
#define RES_FILE_PATH "/Users/vladyslav/Documents/programing/mosaic/software/\
img/processed_image.bmp"
#define	TILE_SIZE 10
#define SUTURE_SIZE 1
#define B 0
#define G 1
#define R 2
#define A 3

#endif
