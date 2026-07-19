#include "loader.h"
#include "elf.h"

#include <stdio.h>
#include <stdlib.h>

FILE *elf_file = NULL;
Elf32_Ehdr elf_header;

bool read_elf_header()
{
    if (fread(&elf_header, sizeof(Elf32_Ehdr), 1, elf_file) != 1)
    {
        perror("Failed to read ELF header");
        return false;
    }
    return true;
}

bool validate_elf_header()
{
    if (elf_header.e_ident[EI_MAG0] != ELFMAG0 ||
        elf_header.e_ident[EI_MAG1] != ELFMAG1 ||
        elf_header.e_ident[EI_MAG2] != ELFMAG2 ||
        elf_header.e_ident[EI_MAG3] != ELFMAG3)
    {
        printf("Invalid ELF magic number\n");
        return false;
    }

    return true;
}

bool validate_elf_support()
{
    if (elf_header.e_ident[EI_CLASS] != ELFCLASS32)
    {
        printf("Unsupported ELF class: %d\n", elf_header.e_ident[EI_CLASS]);
        return false;
    }

    if (elf_header.e_ident[EI_DATA] != ELFDATA2LSB)
    {
        printf("Unsupported ELF data encoding: %d\n", elf_header.e_ident[EI_DATA]);
        return false;
    }

    if (elf_header.e_machine != EM_386)
    {
        printf("Unsupported ELF machine type: %d\n", elf_header.e_machine);
        return false;
    }

    if (elf_header.e_type != ET_EXEC)
    {
        printf("Unsupported ELF file type: %d\n", elf_header.e_type);
        return false;
    }

    return true;
}

bool load_elf(const char *path)
{
    printf("Path: %s\n", path);

    elf_file = fopen(path, "rb");
    if (!elf_file)
    {
        perror("Failed to open file");
        return false;
    }

    if (!read_elf_header())
    {
        fclose(elf_file);
        return false;
    }

    if (!validate_elf_header())
    {
        printf("Invalid ELF file\n");
        fclose(elf_file);
        return false;
    }
    printf("Valid ELF file\n");

    return true;
}