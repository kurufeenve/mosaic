#include "file_io.h"

/******************************************************************************/
/*                                                                            */
/*       reading the contents of the file                                     */
/*       and writing it into the data var                                     */
/*                                                                            */
/******************************************************************************/

void	readFile(const char *file_name, uint8_t *headers, uint8_t **data)
{
	int		fd;
	int		image_size;
	uint8_t		*tresh_buf;

	if ((fd = open(file_name, O_RDONLY)) < 3)
	{
		perror("function: readFile\nfailed to open the file\n");
		exit(EXIT_FAILURE);
	}
	if (read(fd, headers, FULL_HEADER_SIZE) <= 0)
	{
		perror("function: readFile\nfailed to read the header from the file\n");
		exit(EXIT_FAILURE);
	}

	image_size = ((Headers *)headers)->file_h.bfOffBits - FULL_HEADER_SIZE;
	tresh_buf = (uint8_t *)malloc(sizeof(uint8_t) * image_size);
	if (read(fd, tresh_buf, image_size) <= 0)
	{
		perror("function: readFile\nfailed to read the tresh from the file\n");
		exit(EXIT_FAILURE);
	}
	free(tresh_buf);

	image_size = ((Headers *)headers)->file_h.bfSize
		- ((Headers *)headers)->file_h.bfOffBits;
	*data = (uint8_t *)malloc(sizeof(uint8_t) * image_size);
	if (read(fd, *data, image_size) <= 0)
	{
		perror("function: readFile\nfailed to read the data from the file\n");
		exit(EXIT_FAILURE);
	}

	close(fd);
}

/*****************************************************************************/
/*                                                                           */
/*       writing palette to a file                                           */
/*                                                                           */
/*****************************************************************************/

void	writeFile(const char *file_name, const char *string)
{
	int	fd;
	mode_t	modes;

	modes = S_IRWXU|S_IRGRP|S_IROTH;
	if ((fd = open(file_name, O_CREAT|O_EXCL|O_WRONLY, modes)) < 3)
	{
		printf("fd = %d\tfile_name = %s\n", fd, file_name);
		perror("function: writeFile\nfailed to open the file\n");
		exit(EXIT_FAILURE);
	}
	if (write(fd, (void *)string, ft_strlen(string)) <= 0)
	{
		perror("function: writeFile\nfailed to write the palette to the file\n");
		exit(EXIT_FAILURE);
	}
}
