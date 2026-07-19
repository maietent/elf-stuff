#include "loader.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 2) 
    {
        printf("Usage: %s <path>\n", argv[0]);
        return 1;
    }

    if (!load_elf(argv[1])) 
    {
        printf("Failed to load: %s\n", argv[1]);
        return 1;
    }

    return 0;
}