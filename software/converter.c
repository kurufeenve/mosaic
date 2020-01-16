#include "converter.h"

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

void	image_processing(uint8_t *bytes, size_t len, size_t start_from)
{
	for (; start_from < len; start_from++)
	{
		bytes[start_from] = 0xff;
	}
}

void	file_buffering(char *file_name, uint8_t **data, t_headers *headers)
{
	int		fd;
	uint8_t	buff[1];
	uint8_t	headers_buff[FULL_HEADER_SIZE];
	size_t	offset;
	
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		printf("error during file openning\n");
		exit(1);
	}
	if (read(fd, headers_buff, FULL_HEADER_SIZE) <= 0)
	{
		printf("reading error\n");
		exit(1);
	}

	memcpy((uint8_t *)&headers->file_header, headers_buff, sizeof(FileHeader));
	memcpy((uint8_t *)&headers->image_header, (headers_buff + sizeof(FileHeader)), sizeof(InfoHeader));
	*data = (uint8_t *)malloc(sizeof(uint8_t) * headers->file_header.bfSize);
	printf("headers->file_header->bfSize = %d\n", headers->file_header.bfSize);
	memcpy(*data, headers_buff, FULL_HEADER_SIZE);
	offset = FULL_HEADER_SIZE;
	for (uint32_t i = FULL_HEADER_SIZE; i < headers->file_header.bfSize; i++)
	{
		if (read(fd, buff, 1) <= 0)
		{
			printf("reading error\n");
			exit(1);
		}
		memcpy(*data + offset, buff, 1);
		offset++;
	}
	close(fd);
}

void	write_to_file(uint8_t *data, size_t len)
{
	int		fd;

	fd = open(RES_FILE_PATH, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0)
	{
		printf("error during file openning for writing\n");
		exit(1);
	}
	if (write(fd, data, len) <= 0)
	{
		printf("reading error\n");
		exit(1);
	}
	close(fd);
}

int		main(int argc, char** argv)
{
	t_headers	headers;
	uint8_t		*file_data;

	if (argc != 2)
	{
		printf("wrong number of arguments\n");
		return(0);
	}
	file_buffering(argv[1], &file_data, &headers);
	image_processing(file_data, headers.file_header.bfSize, headers.file_header.bfOffBits);
	write_to_file(file_data, headers.file_header.bfSize);
	system("leaks a.out");
	return(0);
}
