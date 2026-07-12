// src/smtp_client.c

#include "smtp_client.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int smtp_read(int fd)
{
    char buf[4096];

    int n = recv(fd, buf, sizeof(buf)-1, 0);

    if(n > 0)
    {
        buf[n] = 0;
        printf("%s", buf);
    }

    return n;
}

static void smtp_write(int fd, const char *cmd)
{
    send(fd, cmd, strlen(cmd), 0);
}

int smtp_send(smtp_client_t *client)
{
    struct hostent *host =
        gethostbyname(client->server);

    if(!host)
        return -1;

    int fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;

    memset(&addr,0,sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(client->port);

    memcpy(&addr.sin_addr,
           host->h_addr,
           host->h_length);

    if(connect(fd,
               (struct sockaddr *)&addr,
               sizeof(addr)) != 0)
    {
        return -1;
    }

    smtp_read(fd);

    smtp_write(fd,"EHLO kubu-mta\r\n");
    smtp_read(fd);

    char buffer[512];

    sprintf(buffer,
            "MAIL FROM:<%s>\r\n",
            client->sender);

    smtp_write(fd,buffer);
    smtp_read(fd);

    sprintf(buffer,
            "RCPT TO:<%s>\r\n",
            client->recipient);

    smtp_write(fd,buffer);
    smtp_read(fd);

    smtp_write(fd,"DATA\r\n");
    smtp_read(fd);

    FILE *fp = fopen(client->message_file,"rb");

    if(fp)
    {
        char line[4096];

        while(fgets(line,sizeof(line),fp))
            smtp_write(fd,line);

        fclose(fp);
    }

    smtp_write(fd,"\r\n.\r\n");
    smtp_read(fd);

    smtp_write(fd,"QUIT\r\n");

    close(fd);

    return 0;
}
