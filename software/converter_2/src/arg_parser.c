#include "arg_parser.h"

/*****************************************************************************/
/*                                                                           */
/*       Get mesh color from arguments                                       */
/*                                                                           */
/*****************************************************************************/

static void    get_mesh_color(Converter *C, char *color)
{
    char    channel[2];
    int     color_len;

    color_len = ft_strlen(color);
    if (color_len == 8 || color_len == 6)
    {
        for (int i = 0; i < ft_strlen(color); i+=2)
        {
            memcpy((void *)channel, (void *)&color[i], 2);
            C->mesh_color.channel[i / 2] = ft_atoi_base(channel, 16);
        }
        if (color_len == 6)
        {
            C->mesh_color.channel[A] = 0xFF;
        }
    }
    else
    {
        perror("Wrong color length inserted."
                " Please, check help for more information.\n");
        exit(EXIT_SUCCESS);
    }
}

/*****************************************************************************/
/*                                                                           */
/*       Parses arguments and copies them into converter structure           */
/*                                                                           */
/*****************************************************************************/

void	args_parse(Converter *C, int argc, char **argv)
{
	char	help[] = "./converter /path/image_name width height mesh_color"
        " path_to_palette.hex\n"
        "physical size should be given in mm\n"
        "mesh_color shoud be 3 or 4 bytes in HEX BGR or BGRA\n";
    size_t  path_len;

	if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'h')
	{
		printf("HELP:\n%s\n", help);
        collect_garbage(C);
		exit(EXIT_SUCCESS);
	}
	else if (argc != ARGS_NUM)
	{
		printf("wrong number of arguments\n%s\n", help);
        collect_garbage(C);
		exit(EXIT_SUCCESS);
	}
    path_len = ft_strlen(argv[1]);
    C->img_name = ft_strnew(path_len);
    memcpy(C->img_name, argv[1], path_len);
    C->phys_size[X] = ft_atoi(argv[2]);
    C->phys_size[Y] = ft_atoi(argv[3]);
    get_mesh_color(C, argv[4]);
    path_len = ft_strlen(argv[5]);
    C->palette_name = ft_strnew(path_len);
    memcpy(C->palette_name, argv[5], path_len);
}
