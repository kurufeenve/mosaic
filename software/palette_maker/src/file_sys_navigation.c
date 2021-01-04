#include "file_sys_navigation.h" 

/******************************************************************************/
/*                                                                            */
/*	 concatinating dir path and file name                                 */
/*	 to get the file path                                                 */
/*	 do not forget to free(file_path)                                     */
/*                                                                            */
/******************************************************************************/

void	getFilePath(char **file_path,
		const char *folder_name,
		const char *file_name)
{
	char	*buf;

	if (folder_name[ft_strlen(folder_name) - 1] != '/')
	{
		buf = ft_strjoin(folder_name, "/");
		*file_path = ft_strjoin(buf, file_name);
		free(buf);
	}
	else
	{
		*file_path = ft_strjoin(folder_name, file_name);
	}
}

/******************************************************************************/
/*                                                                            */
/*       checking the bumber of files                                         */
/*       with needed extension                                                */
/*                                                                            */
/******************************************************************************/

int		filesNum(char *dir_name, char *file_ext)
{
	DIR				*folder;
    struct dirent	*entry;
	int				sum;

	sum = 0;
	folder = opendir(dir_name);
	if(folder == NULL)
    {
        perror("filesNum\nUnable to read director\n");
        exit(EXIT_FAILURE);
    }

	while( (entry = readdir(folder)) )
    {
		if (!(memcmp((void *)(&entry->d_name[ft_strlen(entry->d_name) - BMP_LEN]), (void *)file_ext, ft_strlen(file_ext))))
		{	
        	sum++;
		}
    }
    closedir(folder);
	return (sum);
}

/******************************************************************************/
/*                                                                            */
/*       reading directory                                                    */
/*       checking files by file extentions                                    */
/*       filing the palette structure with file names                         */
/*                                                                            */
/******************************************************************************/

void	readDir(Palette *P)
{
	DIR				*folder;
	struct dirent	*entry;

	P->files_num = filesNum(P->folder_name, BMP);

	folder = opendir(P->folder_name);
	if (!(P->files = (char **)malloc(sizeof(char *) * P->files_num)))
	{
		perror("readDir\nmalloc error\n");
		exit(EXIT_FAILURE);
	}
	P->files_num = 0;

	while( (entry = readdir(folder)) )
	{
		if (!(memcmp((void *)(&entry->d_name[ft_strlen(entry->d_name) - BMP_LEN]), (void *)BMP, BMP_LEN)))
		{
			getFilePath(&(P->files[P->files_num]), P->folder_name, entry->d_name);
			P->files_num++;
		}
	}
    closedir(folder);
}
