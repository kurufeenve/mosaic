#include "garbage_collector.h"

/******************************************************************************/
/*                                                                            */
/*       Collects and frees all allocated memory                              */
/*       that was not freed in the end of the program                         */
/*                                                                            */
/******************************************************************************/

void	collect_garbage(Converter *C)
{
    if (C->img_name != NULL)
    {
	    free(C->img_name);
    }
    if (C->data != NULL)
    {
        free(C->data);
    }
}
