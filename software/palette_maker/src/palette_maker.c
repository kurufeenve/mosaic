#include "palette_maker.h"

int		main(int argc, char **argv)
{
	Palette		P;
	char		help[] = "./palette_maker dirname /path/palette_name\n";

	if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'h')
	{
		printf("HELP:\n%s\n", help);
		return (0);
	}
	else if (argc != 3)
	{
		printf("wrong number of arguments\n%s\n", help);
		return (0);
	}
	memset((void *)(&P), 0, sizeof(P));
	P.folder_name = ft_strnew(ft_strlen(argv[1]));
	ft_strcpy(P.folder_name, argv[1]);
	P.palette_name = ft_strnew(ft_strlen(argv[2]));
	ft_strcpy(P.palette_name, argv[2]);
	readDir(&P);
	converter(&P);
	//system("leaks palette_maker");
	return (0);
}
