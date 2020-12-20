#include "converter.h"

Pixel_T	Get_Pixel(uint8_t *img, uint32_t x, uint32_t y)
{
	Pixel_T	Pixel;

	ft_memcpy((void *)&Pixel.color, (void *)&img[y + x * 4], 4);
	return Pixel;
}

void	Put_Pixel(void *M, int pixel, void	*color)
{
	Mosaic_T	*Mosaic;
	Pixel_T		*col;

	col = (Pixel_T *)color;
	Mosaic = (Mosaic_T *)M;
	Mosaic->image[pixel + B] = col->chanel[B];
	Mosaic->image[pixel + G] = col->chanel[G];
	Mosaic->image[pixel + R] = col->chanel[R];
	Mosaic->image[pixel + A] = col->chanel[A];
}

void	Add_Color(void *M, int pixel, void *place_holder)
{
	Mosaic_T	*Mosaic;

	Mosaic = (Mosaic_T *)M;
	Mosaic->Tiles.blue += Mosaic->image[pixel + B];
	Mosaic->Tiles.green += Mosaic->image[pixel + G];
	Mosaic->Tiles.red += Mosaic->image[pixel + R];
}

void	Match_Color_Euclidean(void *M)
{
	uint32_t	color_number;
	int64_t		delta_chanel[3];
	uint64_t	dE;
	uint64_t	dE_prev;
	Mosaic_T	*Mosaic;

	Mosaic = (Mosaic_T *)M;
	color_number = 0;
	dE_prev = -1;
	for(uint32_t i = 0; i < Mosaic->Palette.size; i++)
	{
		delta_chanel[R] = Mosaic->Tiles.red - Mosaic->Palette.Pixel[i].chanel[R];
		delta_chanel[G] = Mosaic->Tiles.green - Mosaic->Palette.Pixel[i].chanel[G];
		delta_chanel[B] = Mosaic->Tiles.blue - Mosaic->Palette.Pixel[i].chanel[B];
		delta_chanel[R] *= delta_chanel[R];
		delta_chanel[G] *= delta_chanel[G];
		delta_chanel[B] *= delta_chanel[B];
		dE = delta_chanel[R] + delta_chanel[G] + delta_chanel[B];
		if (dE < dE_prev)
		{
			dE_prev = dE;
			color_number = i;
		}
	}
	Mosaic->Tiles.red = Mosaic->Palette.Pixel[color_number].chanel[R];
	Mosaic->Tiles.green = Mosaic->Palette.Pixel[color_number].chanel[G];
	Mosaic->Tiles.blue = Mosaic->Palette.Pixel[color_number].chanel[B];
	Mosaic->Tiles.Tile_Color.chanel[R] = (uint8_t)Mosaic->Palette.Pixel[color_number].chanel[R];
	Mosaic->Tiles.Tile_Color.chanel[G] = (uint8_t)Mosaic->Palette.Pixel[color_number].chanel[G];
	Mosaic->Tiles.Tile_Color.chanel[B] = (uint8_t)Mosaic->Palette.Pixel[color_number].chanel[B];
	Mosaic->Tiles.Tile_Color.chanel[A] = 0xFF;
}

void	Find_Color(Mosaic_T *Mosaic, void (*f)(void *))
{
	uint64_t	number_of_pixels;
	uint32_t	color_number;

	number_of_pixels = TILE_SIZE * Mosaic->Tiles.pixels_per_mm_x * TILE_SIZE * Mosaic->Tiles.pixels_per_mm_y;
	Mosaic->Tiles.blue /= number_of_pixels;
	Mosaic->Tiles.green /= number_of_pixels;
	Mosaic->Tiles.red /= number_of_pixels;
	f((void *)Mosaic);
}

void	Mesh_Coloring(Mosaic_T *Mosaic)
{
	uint32_t	x, y, i, width, height, start;

	width = Mosaic->Headers.Image_Header.biWidth;
	height = Mosaic->Headers.Image_Header.biHeight;
	start = Mosaic->Headers.File_Header.bfOffBits;
	for (y = 0; y < height; y += (TILE_SIZE + SUTURE_SIZE))
	{
		for(x = 0; x < width; x++)
		{
			i = x * 4 + y * width * 4 + start;
			Mosaic->image[i + R] = Mosaic->Mesh_Color.chanel[R];
			Mosaic->image[i + G] = Mosaic->Mesh_Color.chanel[G];
			Mosaic->image[i + B] = Mosaic->Mesh_Color.chanel[B];
			Mosaic->image[i + A] = Mosaic->Mesh_Color.chanel[A];
		}
	}
	for (x = 0; x < width; x += (TILE_SIZE + SUTURE_SIZE))
	{
		for(y = 0; y < height; y++)
		{
			printf("y = %u", y);
			i = x * 4 + y * width * 4 + start;
			Mosaic->image[i + R] = Mosaic->Mesh_Color.chanel[R];
			Mosaic->image[i + G] = Mosaic->Mesh_Color.chanel[G];
			Mosaic->image[i + B] = Mosaic->Mesh_Color.chanel[B];
			Mosaic->image[i + A] = Mosaic->Mesh_Color.chanel[A];
		}
	}
}

void	Iterate_Pixels(Mosaic_T *Mosaic, int x, int y, void (*f)(void *, int, void *))
{
	int			pixel;

	int	i = (x * TILE_SIZE + x * SUTURE_SIZE + SUTURE_SIZE) * Mosaic->Tiles.pixels_per_mm_x;
	int	tile_x_max = i + TILE_SIZE * Mosaic->Tiles.pixels_per_mm_x;
	for (; i < tile_x_max; i++)
	{
		int	j = (y * TILE_SIZE + y * SUTURE_SIZE + SUTURE_SIZE) * Mosaic->Tiles.pixels_per_mm_y;

		int	tile_y_max = j + TILE_SIZE * Mosaic->Tiles.pixels_per_mm_y;
		for (; j < tile_y_max; j++)
		{
			pixel = j * Mosaic->Headers.Image_Header.biWidth * 4 + i * 4 + Mosaic->Headers.File_Header.bfOffBits;
			f((void *)Mosaic, pixel, &Mosaic->Tiles.Tile_Color);
		}
	}
}

void	Iterate_Tiles(Mosaic_T *Mosaic)
{
	for (int x = 0; x < Mosaic->Tiles.tiles_width; x++)
	{
		int	y = 0;
		for (; y < Mosaic->Tiles.tiles_height; y++)
		{
			Iterate_Pixels(Mosaic, x, y, &Add_Color);
			Find_Color(Mosaic, &Match_Color_Euclidean);
			Iterate_Pixels(Mosaic, x, y, &Put_Pixel);
		}
	}
}

void	Init_Processing(Mosaic_T *Mosaic)
{
	Mosaic->Tiles.tiles_height = (Mosaic->height - 1) / (TILE_SIZE + SUTURE_SIZE);
	Mosaic->Tiles.tiles_width = (Mosaic->width - 1) / (TILE_SIZE + SUTURE_SIZE);

	if ((Mosaic->Headers.Image_Header.biWidth % 11 != 0) || (Mosaic->width % 11 != 0) || (Mosaic->Headers.Image_Header.biHeight % 11 != 0) || ( Mosaic->height % 11 != 0))
	{
		printf("faulty image size or mosaic size");
		exit(0);
	}
	Mosaic->Tiles.pixels_per_mm_x = Mosaic->Headers.Image_Header.biWidth /
		Mosaic->width;
	Mosaic->Tiles.pixels_per_mm_y = Mosaic->Headers.Image_Header.biHeight /
		Mosaic->height;
}

void	Image_Processing(Mosaic_T *Mosaic)
{
	printf("biWidth = %u\n", Mosaic->Headers.Image_Header.biWidth);
	Init_Processing(Mosaic);
	Iterate_Tiles(Mosaic);
	Mesh_Coloring(Mosaic);
}

void	File_Buffering(char *file_name, uint8_t **data, Headers_T *Headers)
{
	int		fd;
	uint8_t	buff[1];
	uint8_t	headers_buff[FULL_HEADER_SIZE];
	size_t	offset;

	double		start;
	double		end;
	
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror("error during file openning\n");
		exit(1);
	}
	if (read(fd, headers_buff, FULL_HEADER_SIZE) <= 0)
	{
		perror("reading error\n");
		exit(1);
	}

	memcpy((uint8_t *)&Headers->File_Header, headers_buff, sizeof(FileHeader));
	memcpy((uint8_t *)&Headers->Image_Header, (headers_buff + sizeof(FileHeader)), sizeof(InfoHeader));

	start = clock();
	*data = (uint8_t *)malloc(sizeof(uint8_t) * Headers->File_Header.bfSize);
	end = clock();
	printf("allocating memory = %f\n", TIME_DIFF(start, end));
	
	printf("Headers->File_Header->bfSize = %d\n", Headers->File_Header.bfSize);
	memcpy(*data, headers_buff, FULL_HEADER_SIZE);
	printf("Pixel height = %d\npixel width = %d\n", 
			Headers->Image_Header.biHeight, Headers->Image_Header.biWidth);
	offset = FULL_HEADER_SIZE;

	start = clock();
	for (uint32_t i = FULL_HEADER_SIZE; i < Headers->File_Header.bfSize; i++)
	{
		if (read(fd, buff, 1) <= 0)
		{
			perror("reading error\n");
			exit(1);
		}
		memcpy(*data + offset, buff, 1);
		offset++;
	}
	end = clock();
	printf("reading file = %f\n", TIME_DIFF(start, end));
	
	close(fd);
}

void	Write_To_File(uint8_t *data, size_t len)
{
	int		fd;

	//ft_putendl("processed image");
	//ft_print_bytes((void *)&data[4546], 16);
	fd = open(RES_FILE_PATH, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0)
	{
		perror("error during file openning for writing\n");
		exit(1);
	}
	if (write(fd, data, len) <= 0)
	{
		perror("reading error\n");
		exit(1);
	}
	close(fd);
	system("chmod 755 img/processed_image.bmp");
}

void	Read_Palette(Mosaic_T *Mosaic)
{
	int		fd;
	char	color_buf[8];
	Pixel_T	Pixel;
	int		r_ch;

	ft_bzero((void *)&Pixel, sizeof(Pixel_T));
	fd = open(Mosaic->palette_name, O_RDONLY);
	if (fd < 0)
	{
		perror("error during file openning\n");
		exit(1);
	}
	r_ch = 1;
	while (r_ch)
	{
		r_ch = read(fd, color_buf, 8);
		if (r_ch <= 0)
		{
			break ;
		}
		Pixel.color = ft_atoi_base((const char *)color_buf, 16);
		Pixel.chanel[A] = 0xFF;
		Mosaic->Palette.Pixel = (Pixel_T *)ft_memjoin(
		(void *)Mosaic->Palette.Pixel, (void *)&Pixel,
		Mosaic->Palette.size * sizeof(Pixel_T), sizeof(Pixel_T));

		/*ft_putstr("Pixel[");
		ft_putnbr(Mosaic->Palette.size);
		ft_putstr("] = ");
		ft_print_bytes((void *)&Mosaic->Palette.Pixel[Mosaic->Palette.size].color, 4);*/
		Mosaic->Palette.size++;
	}
	//printf("Palette size = %u\n", Mosaic->Palette.size);
	close(fd);
	if (Mosaic->Palette.size <= 0)
	{
		perror("Palette is empty\n");
		exit(1);
	}
}

void	Init(Mosaic_T *Mosaic, char **argv)
{
	Mosaic->Mesh_Color.color = ft_atoi_base(argv[2], 16);
	Mosaic->palette_name = argv[3];
	Mosaic->height = (uint32_t)ft_atoi(argv[4]);
	Mosaic->width = (uint32_t)ft_atoi(argv[5]);
	Read_Palette(Mosaic);

	Mosaic->Speed.start = clock();
	File_Buffering(argv[1], &Mosaic->image, &Mosaic->Headers);
	Mosaic->Speed.end = clock();
	printf("File_Buffering = %f\n", TIME_DIFF(Mosaic->Speed.start, Mosaic->Speed.end));

}

int		main(int argc, char** argv)
{
	Mosaic_T	Mosaic;
	double		start;
	double		end;

	Mosaic.Speed.start = start = clock();
	ft_bzero(&Mosaic, sizeof(Mosaic));
	Mosaic.Speed.end = clock();
	printf("ft_bzero = %f\n", TIME_DIFF(Mosaic.Speed.start, Mosaic.Speed.end));
	
	if (argc != 6)
	{
		printf("wrong number of arguments\n"
		"./converter image_name mesh_color palette height width\n"
		"height and width in mm multiple of 11\n");
		return(0);
	}

	Mosaic.Speed.start = clock();
	Init(&Mosaic, argv);
	Mosaic.Speed.end = clock();
	printf("Init = %f\n", TIME_DIFF(Mosaic.Speed.start, Mosaic.Speed.end));
	
	Image_Processing(&Mosaic);
	Write_To_File(Mosaic.image, Mosaic.Headers.File_Header.bfSize);
	end = clock();
	printf("total time = %f\n", TIME_DIFF(start, end));
	system("leaks converter");
	return(0);
}
