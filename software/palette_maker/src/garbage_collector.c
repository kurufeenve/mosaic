#include "garbage_collector.h"

/******************************************************************************/
/*                                                                            */
/*       Collects and frees all allocated memory                              */
/*       that was not freed in the end of the program                         */
/*                                                                            */
/******************************************************************************/

void	collect_garbage(Palette *P)
{
    if (P->folder_name != NULL)
    {
	    free(P->folder_name);
    }
    if (P->palette_name != NULL)
    {
        free(P->palette_name);
    }
    if (P->files != NULL)
    {
        for (int i = 0; i < P->files_num; i++)
        {
            if (P->files[i] != NULL)
            {
                free(P->files[i]);
            }
        }
        free(P->files);
    }
}
