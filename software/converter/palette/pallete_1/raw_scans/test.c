#include <stdio.h>
#include <string.h>

int	main(void)
{
	float			original;
	unsigned int	fucked_up_var;
	float			cast;
	float			ptr_cast;

	original = 4000;
	//memcpy(((void *)(&fucked_up_var)), ((void *)(&fucked_up_var)), 4);
	fucked_up_var = *((unsigned int *)(&original));
	ptr_cast = *((float *)(&fucked_up_var));
	cast = (float) fucked_up_var;
	printf("original = %f\nfucked_up_var = %u\ncast = %f\nptr_cast = %f\n", original, fucked_up_var, cast, ptr_cast);
	return (0);
}
