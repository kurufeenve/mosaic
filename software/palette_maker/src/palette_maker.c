#include "palette_maker.h"

int		main(int argc, char **argv)
{
	Palette		P;
	
	memset((void *)(&P), 0, sizeof(P));
	args_parse(&P, argc, argv);
	readDir(&P);
	converter(&P);
	collect_garbage(&P);
	return (0);
}
