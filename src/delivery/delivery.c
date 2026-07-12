// src/delivery.c

#include "delivery.h"

#include <dirent.h>
#include <stdio.h>
#include <string.h>

void delivery_init(void)
{
    printf("Delivery engine initialized.\n");
}

void delivery_process_message(const char *path)
{
    printf("Processing: %s\n", path);

    /* Next steps:
       - Parse .eml file
       - Read From/To/Subject
       - Determine destination
       - Deliver locally or remotely
    */
}

void delivery_scan_queue(void)
{
    DIR *dir = opendir("spool/incoming");

    if (!dir)
        return;

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.')
            continue;

        char path[1024];

        snprintf(path,
                 sizeof(path),
                 "spool/incoming/%s",
                 entry->d_name);

        delivery_process_message(path);
    }

    closedir(dir);
}
