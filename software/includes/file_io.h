#ifndef FILE_IO_H
#define FILE_IO_H

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#define RES_FILE_PATH "/mnt/c/Users/Vlad/Desktop/processed_image.bmp\0"

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

typedef struct	s_headers
{
	FileHeader	file_header;
	InfoHeader	image_header;
}				t_headers;

#define FULL_HEADER_SIZE (sizeof(FileHeader) + sizeof(InfoHeader))

void	file_buffering(char *file_name, uint8_t **data, t_headers *headers);
void	write_to_file(uint8_t *data, size_t len);

#endif
