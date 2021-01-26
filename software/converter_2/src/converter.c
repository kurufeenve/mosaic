#include "converter.h"

int     main(int argc, char **argv)
{
    Converter   C;

    memset((void *)&C, 0, sizeof(C));
    args_parse(&C, argc, argv);
    processing(&C);
    collect_garbage(&C);
    system("leaks converter");
    return (0);
}
