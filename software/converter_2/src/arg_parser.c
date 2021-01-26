#include "arg_parser.h"

/*****************************************************************************/
/*                                                                           */
/*       Parses arguments and copies them into converter structure           */
/*                                                                           */
/*****************************************************************************/

void	args_parse(Converter *C, int argc, char **argv)
{
	char	help[] = "./converter /path/image_name\n";

	if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'h')
	{
		printf("HELP:\n%s\n", help);
        collect_garbage(C);
		exit(EXIT_SUCCESS);
	}
	else if (argc != 2)
	{
		printf("wrong number of arguments\n%s\n", help);
        collect_garbage(C);
		exit(EXIT_SUCCESS);
	}
    C->img_name = ft_strnew(ft_strlen(argv[1]));
    memcpy(C->img_name, argv[1], ft_strlen(argv[1]));
}
