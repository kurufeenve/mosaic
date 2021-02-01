#include "arg_parser.h"

/*****************************************************************************/
/*                                                                           */
/*       Parses arguments and copies them into palette structure             */
/*                                                                           */
/*****************************************************************************/

void	args_parse(Palette *P, int argc, char **argv)
{
	char	help[] = "./palette_maker /path/dirname /path/palette_name\n";

	if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'h')
	{
		printf("HELP:\n%s\n", help);
		exit(EXIT_SUCCESS);
	}
	else if (argc != 3)
	{
		printf("wrong number of arguments\n%s\n", help);
		exit(EXIT_SUCCESS);
	}
	P->folder_name = ft_strnew(ft_strlen(argv[1]));
	ft_strcpy(P->folder_name, argv[1]);
	P->palette_name = ft_strnew(ft_strlen(argv[2]));
	ft_strcpy(P->palette_name, argv[2]);
}
