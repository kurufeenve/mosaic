#include "./includes/analyzer.h"
#include "./includes/converter.h"

void	init_test_colors(t_color *test_colors)
{
	test_colors[0].color = 0x65AAC0;
	test_colors[1].color = 0x2082A7;
	test_colors[2].color = 0xB1B42A;
	test_colors[3].color = 0x232D2B;
	test_colors[4].color = 0x606D69;
	test_colors[5].color = 0x6C91AF;
	test_colors[6].color = 0x295B78;
	test_colors[7].color = 0x243677;
	test_colors[8].color = 0xCBC4B7;
	test_colors[9].color = 0xC08C02;
	test_colors[10].color = 0x942B25;
	test_colors[11].color = 0x875638;
	test_colors[12].color = 0x367C55;
	test_colors[13].color = 0xF5F9F8;
	test_colors[14].color = 0x615533;
	test_colors[15].color = 0x8EB6A0;
	test_colors[16].color = 0x585354;
	test_colors[17].color = 0x96916B;
	test_colors[18].color = 0x9D9F8F;
}

int		main(int argc, char** argv)
{
	t_headers	headers;
	uint8_t		*file_data;
	t_color		test_colors[19];

	if (argc != 2)
	{
		printf("wrong number of arguments\n");
		return(0);
	}
	system("rm -rf processed_image.bmp");
	init_test_colors(test_colors);
	file_buffering(argv[1], &file_data, &headers);
	//median_cut(file_data, headers);
	//image_processing(file_data, headers);
	write_to_file(file_data, headers.file_header.bfSize);
	system("leaks a.out");
	return(0);
}
