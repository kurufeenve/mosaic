#include "file_io.h"

/******************************************************************************/
/*                                                                            */
/*       reading the contents of the BMP image                                */
/*       and writing it into the data var                                     */
/*                                                                            */
/******************************************************************************/

uint8_t readBMP(const char *file_name, uint8_t *headers, uint8_t **data)
{
	int         fd;
	int         image_size;
	uint8_t		*tresh_buf;

	if ((fd = open(file_name, O_RDONLY)) < 3)
	{
		perror("function: readBMP\nfailed to open the file\n");
		exit(EXIT_FAILURE);
        return (1);
	}
	if (read(fd, headers, FULL_HEADER_SIZE) <= 0)
	{
		perror("function: readBMP\nfailed to read the header from the file\n");
		exit(EXIT_FAILURE);
        return (1);
	}

    /*
     * In this part of the file palette of colors is located
     * but used it is only when bits per color are <= 8
     */
	image_size = ((Headers *)headers)->file_h.bfOffBits - FULL_HEADER_SIZE;
	tresh_buf = (uint8_t *)malloc(sizeof(uint8_t) * image_size);
	if (read(fd, tresh_buf, image_size) <= 0)
	{
		perror("function: readBMP\nfailed to read the tresh from the file\n");
		exit(EXIT_FAILURE);
        return (1);
	}
	free(tresh_buf);

	image_size = ((Headers *)headers)->file_h.bfSize
		- ((Headers *)headers)->file_h.bfOffBits;
	*data = (uint8_t *)malloc(sizeof(uint8_t) * image_size);
	if (read(fd, *data, image_size) <= 0)
	{
		perror("function: readBMP\nfailed to read the data from the file\n");
		exit(EXIT_FAILURE);
        return (1);
	}

	close(fd);
    return (0);
}
