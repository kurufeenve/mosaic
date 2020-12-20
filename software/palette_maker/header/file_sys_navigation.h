#ifndef FILE_SYS_NAVIGATION_H
#define FILE_SYS_NAVIGATION_H

/* EXTERNAL */
#include <dirent.h>

/* INTERNAL */
#include "common.h"

#define BMP ".bmp"
#define BMP_LEN 4

void	getFilePath(char **file_path,
		const char *folder_name,
		const char *file_name);
void	readDir(Palette *P);
int		filesNum(char *dir_name, char *file_ext);

#endif
