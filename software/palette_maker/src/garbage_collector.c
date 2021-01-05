#include "garbage_collector.h"

/******************************************************************************/
/*                                                                            */
/*       Collects and frees all allocated memory                              */
/*       that was not freed in the end of the program                         */
/*                                                                            */
/******************************************************************************/

void	collect_garbage(Palette *P)
{	
	free(P->folder_name);
	free(P->palette_name);
	for (int i = 0; i < P->files_num; i++)
	{
		free(P->files[i]);
	}
	free(P->files);
}
