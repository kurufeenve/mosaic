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

void	image_processing(uint8_t *bytes, size_t len, size_t offset, size_t start_from)
{
	if (offset + len < start_from)
	{
		return ;
	}
	else if (offset + len > start_from && offset < start_from)
	{
		offset = start_from;
	}
	for (size_t i = offset; i < offset + len; i++)
	{
		bytes[i] = 0xff;
	}
}

void	file_buffering(char *file_name, uint8_t **data, t_headers *headers)
{
	int		fd;
	uint8_t	buff[1];
	uint8_t	headers_buff[FULL_HEADER_SIZE];

	fd = open(file_name, O_RDONLY);
	if (read(fd, headers_buff, FULL_HEADER_SIZE) <= 0)
	{
		printf("reading error\n");
		exit(1);
	}

	headers->file_header = (FileHeader *)headers_buff;
	headers->image_header = (InfoHeader *)(headers_buff + sizeof(FileHeader));
	*data = (uint8_t *)malloc(sizeof(uint8_t) * headers->file_header->bfSize);
	printf("headers->file_header->bfSize = %d\n", headers->file_header->bfSize);
	memcpy(*data, headers_buff, FULL_HEADER_SIZE);
	for (uint32_t i = FULL_HEADER_SIZE; i < headers->file_header->bfSize; i++)
	{
		if (read(fd, buff, FULL_HEADER_SIZE) <= 0)
		{
			printf("reading error\n");
			exit(1);
		}
		memcpy(*data, buff, FULL_HEADER_SIZE);
	}
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
	print_bytes(file_data, 1000);
	/*fd = open(argv[1], O_RDONLY);
	fd_res = open("/mnt/c/Users/Vlad/Desktop/result_image.bmp", O_WRONLY | O_CREAT | O_TRUNC);
	printf("fd_res = %d\n", fd_res);
	if (fd <= 0)
	{
		printf("could not open a file\n");
		exit(1);
	}
	bytes_read = read(fd, buf, FULL_HEADER_SIZE);
	bytes_written = write(fd_res, buf, FULL_HEADER_SIZE);
	printf("bytes_read = %zu\n", bytes_read);
	printf("bytes_written = %zu\n", bytes_written);
	print_bytes(buf, FULL_HEADER_SIZE);
	offset += FULL_HEADER_SIZE - 1;
	
	file_header = (FileHeader *)buf;
	image_header = (InfoHeader *)(buf + sizeof(FileHeader));

	printf("file:\ntype = %#06x\nsize = %d\noffBits = %d\n", \
file_header->bfType, file_header->bfSize, file_header->bfOffBits);
	printf("image:\nsize = %#10x\nwidth = %d\nheight = %d\nbit count = %d\nsize image = %#10x\n", \
image_header->biSize, image_header->biWidth, image_header->biHeight, image_header->biBitCount, \
image_header->biSizeImage);
	printf("file header: and its size is %zu\n", sizeof(FileHeader));
	print_bytes((uint8_t *)file_header, sizeof(FileHeader));
	printf("image header: and its size is %zu\n", sizeof(InfoHeader));
	print_bytes((uint8_t *)image_header, sizeof(InfoHeader));

	while ((bytes_read = read(fd, buf, FULL_HEADER_SIZE)))
	{
		print_bytes(buf, FULL_HEADER_SIZE);
		image_processing(buf, FULL_HEADER_SIZE, offset, file_header->bfOffBits);
		write(fd_res, buf, FULL_HEADER_SIZE);
		offset += bytes_read;
	}
	printf("offset = %zu\n", offset);*/
	return(0);
}
