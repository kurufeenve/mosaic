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

#define BUFF_SIZE 1024

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
	FileHeader	*file_header;
	InfoHeader	*image_header;
}				t_headers;

#define FULL_HEADER_SIZE (sizeof(FileHeader) + sizeof(InfoHeader))

void    print_bytes(uint8_t *bytes, size_t len);

#endif
