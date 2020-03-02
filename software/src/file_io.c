#include "./includes/file_io.h"

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
	if (read(fd, headers_buff, FULL_HEADER_SIZE) <= 1)
	{
		printf("reading error\n");
		exit(1);
	}

	memcpy((void *)&headers->file_header, headers_buff, sizeof(FileHeader));
	memcpy((void *)&headers->image_header, (headers_buff + sizeof(FileHeader)), sizeof(InfoHeader));
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
		printf("writing error\n");
		exit(1);
	}
	close(fd);
	system("chmod 755 processed_image.bmp");
}
