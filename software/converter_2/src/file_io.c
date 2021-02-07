#include "file_io.h"

/******************************************************************************/
/*                                                                            */
/*       easy exit                                                            */
/*                                                                            */
/******************************************************************************/

static void    my_exit(int fd, const char *message)
{
    perror(message);
    close(fd);
    exit(EXIT_FAILURE);
}

/******************************************************************************/
/*                                                                            */
/*       reading the contents of the BMP image                                */
/*       and writing it into the data var                                     */
/*                                                                            */
/******************************************************************************/

void    readBMP(const char *file_name, uint8_t *headers, uint8_t **data)
{
	int         fd;
	int         image_size;

	if ((fd = open(file_name, O_RDONLY)) < 3)
	{
        my_exit(fd, "function: readBMP\nfailed to open the file\n");
	}
	if (read(fd, headers, FULL_HEADER_SIZE) <= 0)
	{
        my_exit(fd, "function: readBMP\n"
                "failed to read the header from the file\n");
	}

	image_size = ((Headers *)headers)->file_h.bfSize
		- ((Headers *)headers)->file_h.bfOffBits;
	*data = (uint8_t *)malloc(sizeof(uint8_t) * image_size);
	if (read(fd, *data, image_size) <= 0)
	{
        my_exit(fd, "function: readBMP\nfailed to read the data"
               " from the file\n");
	}

	close(fd);
}

/******************************************************************************/
/*                                                                            */
/*       writing result of calculations to the BMP file                       */
/*                                                                            */
/******************************************************************************/

void    writeBMP(const char *file_name, Converter C)
{
	int         fd;
	mode_t      modes;
	int         image_size;

	modes = S_IRWXU|S_IRGRP|S_IROTH;
	if ((fd = open(file_name, O_CREAT|O_EXCL|O_WRONLY, modes)) < 3)
	{
        my_exit(fd, "function: writeBMP\nfailed to open the file\n");
	}

	if (write(fd, (void *)&C.headers, FULL_HEADER_SIZE) <= 0)
	{
        my_exit(fd, "function: writeBMP\nfailed to write the header"
                " to the file\n");
	}

	image_size = C.headers.file_h.bfSize - C.headers.file_h.bfOffBits;
	if (write(fd, (void *)C.data, image_size) <= 0)
	{
        my_exit(fd, "function: writeBMP\nfailed to write data to the file\n");
	}
    close(fd);

}

void    readPalette(Converter *C)
{
    int     fd;
    uint8_t buf[8];
    int     res;

	if ((fd = open(C->palette_name, O_RDONLY)) < 3)
	{
        my_exit(fd, "function: readPalette\nfailed to open the file\n");
	}
    res = 1;
    while(res)
    {
        res = read(fd, buf, 8);
    }
}
