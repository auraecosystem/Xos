// src/smtp_server.c

#include "smtp_server.h"

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

struct smtp_server
{
    int listen_fd;
};

smtp_server_t *smtp_server_create(void)
{
    smtp_server_t *server = calloc(1, sizeof(smtp_server_t));

    if (!server)
        return NULL;

    server->listen_fd = -1;

    return server;
}

int smtp_server_start(smtp_server_t *server)
{
    int opt = 1;

    server->listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server->listen_fd < 0)
    {
        perror("socket");
        return -1;
    }

    setsockopt(server->listen_fd,
               SOL_SOCKET,
               SO_REUSEADDR,
               &opt,
               sizeof(opt));

    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;

    /* Development port */
    addr.sin_port = htons(2525);

    if (bind(server->listen_fd,
             (struct sockaddr *)&addr,
             sizeof(addr)) < 0)
    {
        perror("bind");
        return -1;
    }

    if (listen(server->listen_fd, 128) < 0)
    {
        perror("listen");
        return -1;
    }

    printf("KUBU-MTA listening on port 2525...\n");

    return 0;
}

void smtp_server_poll(smtp_server_t *server)
{
    struct sockaddr_in client;
    socklen_t len = sizeof(client);

    int fd = accept(server->listen_fd,
                    (struct sockaddr *)&client,
                    &len);

    if (fd < 0)
        return;

    printf("Connection from %s\n",
           inet_ntoa(client.sin_addr));

    const char greeting[] =
        "220 KUBU-MTA ESMTP Ready\r\n";

    send(fd,
         greeting,
         strlen(greeting),
         0);

    close(fd);
}

void smtp_server_stop(smtp_server_t *server)
{
    if (server->listen_fd >= 0)
        close(server->listen_fd);
}

void smtp_server_destroy(smtp_server_t *server)
{
    free(server);
}
