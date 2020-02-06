#include "./includes/analyzer.h"
#include "./includes/converter.h"

void	init_test_colors(t_color *test_colors)
{
	test_colors[0].color = 0x64AAC1;
	test_colors[1].color = 0x1F81A7;
}

int		main(int argc, char** argv)
{
	t_headers	headers;
	uint8_t		*file_data;
	t_color		test_colors[8];

	if (argc != 2)
	{
		printf("wrong number of arguments\n");
		return(0);
	}
	system("rm -rf processed_image.bmp");
	file_buffering(argv[1], &file_data, &headers);
	median_cut(file_data, headers);
	image_processing(file_data, headers);
	write_to_file(file_data, headers.file_header.bfSize);
	system("leaks a.out");
	return(0);
}
