#include <stdio.h>
#include <Windows.h>

INT64 extCode(const char *ext)
{
    if (ext == NULL)
    {
        return 0;
    }
    INT64 rc = 0;
    strncpy(&rc, ext, sizeof(rc));
    return rc;
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        printf("#define EXT_%s 0x%llx\n", argv[i], extCode(argv[i]));
    }
    return 0;
}