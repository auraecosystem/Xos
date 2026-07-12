// src/smtp_server.c

#include <stdio.h>
#include <stdlib.h>

#include "smtp_server.h"

struct smtp_server
{
    int listen_fd;
};

smtp_server_t *smtp_server_create(void)
{
    smtp_server_t *s = calloc(1, sizeof(*s));
    return s;
}

int smtp_server_start(smtp_server_t *s)
{
    (void)s;

    printf("SMTP server starting...\n");

    return 0;
}

void smtp_server_poll(smtp_server_t *s)
{
    (void)s;

    /* Event loop will be implemented here */
}

void smtp_server_stop(smtp_server_t *s)
{
    (void)s;

    printf("SMTP server stopped.\n");
}

void smtp_server_destroy(smtp_server_t *s)
{
    free(s);
}
