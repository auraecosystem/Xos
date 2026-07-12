// src/queue.c

#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
#else
#include <sys/stat.h>
#endif

static void make_id(char *id)
{
    sprintf(id,
        "%ld-%u",
        time(NULL),
        (unsigned)rand());
}

int queue_init(void)
{
    mkdir("spool",0755);
    mkdir("spool/incoming",0755);

    return 0;
}

int queue_store(smtp_message_t *msg,
                const char *data)
{
    make_id(msg->id);

    sprintf(msg->filename,
            "spool/incoming/%s.eml",
            msg->id);

    FILE *fp = fopen(msg->filename,"wb");

    if(fp==NULL)
        return -1;

    fwrite(data,
           1,
           strlen(data),
           fp);

    fclose(fp);

    return 0;
}
