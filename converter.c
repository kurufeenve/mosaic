//#include "converter.h"

#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

struct tagBITMAPFILEHEADER
{
        uint16_t     bfType;
        uint32_t     bfSize;
        uint16_t     bfReserved1;
        uint16_t     bfReserved2;
        uint32_t     bfOffBits;
} __attribute__((__packed__,__aligned__(1)));

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
} BITMAPINFOHEADER;

#define FULL_HEADER_SIZE (sizeof(struct tagBITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER))

void	print_bytes(uint8_t *bytes, size_t len)
{
	for(size_t i = 0; i < len; i++)
	{
		printf("%02x ", bytes[i]);
		if (!(i % 16) && i != 0)
		{
			printf("\n");
		}
	}
	printf("\n");
}

int		main(int argc, char** argv)
{
	int					fd;
	uint8_t				buf[FULL_HEADER_SIZE];
	size_t				bytes_read;
	size_t				offset;
	//BITMAPFILEHEADER	file_header;
	//BITMAPINFOHEADER	image_header;
	int					size;

	offset = 0;
	if (argc != 2)
	{
		printf("wrong number of arguments\n");
		return(0);
	}
	fd = open(argv[1], O_RDONLY);
	printf("fd = %d\n", fd);
	if (fd <= 0)
	{
		printf("could not open a file\n");
		exit(1);
	}
	bytes_read = read(fd, buf, FULL_HEADER_SIZE);
	printf("bytes_read = %zu\n", bytes_read);
	print_bytes(buf, FULL_HEADER_SIZE);
	offset += FULL_HEADER_SIZE;
	//file_header = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
	//memcpy((uint8_t *)file_header, buf, sizeof(BITMAPFILEHEADER));
	//&file_header = (BITMAPFILEHEADER *)buf;
	//&image_header = (BITMAPINFOHEADER *)(buf + sizeof(BITMAPFILEHEADER));
	/*printf("file:\ntype = %#06x\nsize = %#06x\noffBits = %#10x\n", \
file_header->bfType, file_header->bfSize, file_header->bfOffBits);
	printf("image:\nsize = %#10x\nwidth = %d\nheight = %d\nbit count = %#06x\nsize image = %#10x\n", \
image_header->biSize, image_header->biWidth, image_header->biHeight, image_header->biBitCount, \
image_header->biSizeImage);*/
	size = sizeof(struct tagBITMAPFILEHEADER);
	printf("file header: and its size is %d\n", size);
	//print_bytes((uint8_t *)&file_header, sizeof(BITMAPFILEHEADER));
	printf("image header: and its size is %zu\n", sizeof(BITMAPINFOHEADER));
	//print_bytes((uint8_t *)&image_header, sizeof(BITMAPINFOHEADER));
	return(0);
}
