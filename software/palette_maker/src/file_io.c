#include "file_io.h"

/********************************************/
/*											*/
/*	reading the contents of the file and	*/
/*	writing it into the data var			*/
/*											*/
/********************************************/

void	readFile(const char *file_name, uint8_t *headers, uint8_t **data)
{
	int		fd;
	int		image_size;
	uint8_t	*tresh_buf;

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

	printf("bfSize = %d\tbfOffbits = %d\tfull header size = %lu\tbiSize = %d\n",
			((Headers *)headers)->file_h.bfSize,
			((Headers *)headers)->file_h.bfOffBits,
			FULL_HEADER_SIZE,
			((Headers *)headers)->info_h.biSize);
	
	image_size = ((Headers *)headers)->file_h.bfOffBits - FULL_HEADER_SIZE;
	printf("reading enneeded info = %d bytes\n", image_size);
	tresh_buf = (uint8_t *)malloc(sizeof(uint8_t) * image_size);
	if (read(fd, tresh_buf, image_size) <= 0)
	{
		perror("function: readFile\nfailed to read the tresh from the file\n");
		exit(EXIT_FAILURE);
	}
	for (int i = FULL_HEADER_SIZE; i < image_size; i+=4)
	{
		printf("%08x\n", *(uint32_t *)(&data[0][i]));
	}
	free(&tresh_buf);

	image_size = ((Headers *)headers)->file_h.bfSize - ((Headers *)headers)->file_h.bfOffBits;

	printf("image_size = %d\n", image_size);

	*data = (uint8_t *)malloc(sizeof(uint8_t) * image_size);

	if (read(fd, *data, image_size) <= 0)
	{
		perror("function: readFile\nfailed to read the data from the file\n");
		exit(EXIT_FAILURE);
	}

	/*for (int i = ((Headers *)headers)->file_h.bfOffBits; i < image_size; i+=4)
	{
		printf("%08x\n", *(uint32_t *)(&data[0][i]));
	}*/
	printf("==================\n");
	close(fd);

	/*if ((fd = open(file_name, O_RDONLY)) < 3)
	{
		perror("function: readFile\nfailed to open the file\n");
		exit(EXIT_FAILURE);
	}
	uint8_t	buf[1];
	while(read(fd, buf, 1))
	{
		printf("%02x", buf[0]);
	}
	printf("\n==================\n");
	close(fd);*/
}

