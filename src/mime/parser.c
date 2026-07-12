// src/mime/parser.c

#include "mime.h"

#include <stdio.h>
#include <string.h>

int mime_parse(FILE *fp)
{
    char line[4096];

    while (fgets(line, sizeof(line), fp))
    {
        if (strcmp(line, "\n") == 0 ||
            strcmp(line, "\r\n") == 0)
            break;

        printf("%s", line);
    }

    return 0;
}
