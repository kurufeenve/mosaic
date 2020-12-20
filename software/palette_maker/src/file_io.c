#include "file_io.h"

/********************************************/
/*											*/
/*	reading the contents of the file and	*/
/*	writing it into the data var			*/
/*											*/
/********************************************/

void	readFile(const char *file_name, uint8_t *headers, uint8_t *data)
{
	int		fd;

	if ((fd = open(file_name, O_RDONLY)) < 3)
	{
		perror("readFile\nfailed to open the file\n");
		exit(EXIT_FAILURE);
	}
	if (read(fd, headers, FULL_HEADER_SIZE) <= 0)
	{
		perror("readFile\nfailed to read the file\n");
		exit(EXIT_FAILURE);
	}

	printf("bfSize = %d\tbfOffbits = %d\tfull header size = %lu\tbiSize = %d\n",
			((Headers *)headers)->file_h.bfSize,
			((Headers *)headers)->file_h.bfOffBits,
			FULL_HEADER_SIZE,
			((Headers *)headers)->info_h.biSize);
	
	data = (uint8_t *)malloc(sizeof(uint8_t) *
			(((Headers *)headers)->file_h.bfSize -
			 ((Headers *)headers)->file_h.bfOffBits));

	if (read(fd, headers, FULL_HEADER_SIZE) <= 0)
	{
		perror("readFile\nfailed to read the file\n");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

