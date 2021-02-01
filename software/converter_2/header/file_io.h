#ifndef FILE_IO_H
#define FILE_IO_H

/* EXTERNAL */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* INTERNAL */
#include "common.h"

void    readBMP(const char *file_name, uint8_t *headers, uint8_t **data);
void    writeBMP(const char *file_name, Converter C);

#endif
