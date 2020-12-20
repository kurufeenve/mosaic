#include "palette_maker.h"

int		main(int argc, char **argv)
{
	Palette		P;

	if (argc != 3)
	{
		printf("wrong number of arguments\n"
				"./palette_maker dirname palette_name\n");
		return (0);
	}
	memset((void *)(&P), 0, sizeof(P));
	P.folder_name = ft_strnew(ft_strlen(argv[1]));
	ft_strcpy(P.folder_name, argv[1]);
	P.palette_name = ft_strnew(ft_strlen(argv[2]));
	ft_strcpy(P.palette_name, argv[1]);
	readDir(&P);
	converter(&P);
	system("leaks palette_maker");
	return (0);
}
