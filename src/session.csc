// src/session.cc

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

static void smtp_reply(int fd, const char *msg)
{
    write(fd, msg, strlen(msg));
}

void smtp_session(int fd)
{
    char buffer[BUFFER_SIZE];

    smtp_reply(fd, "220 KUBU-MTA ESMTP Ready\r\n");

    while (1)
    {
        memset(buffer, 0, sizeof(buffer));

        int n = read(fd, buffer, sizeof(buffer) - 1);

        if (n <= 0)
            break;

        printf("CLIENT: %s", buffer);

        if (strncmp(buffer, "HELO", 4) == 0)
        {
            smtp_reply(fd, "250 Hello\r\n");
        }
        else if (strncmp(buffer, "EHLO", 4) == 0)
        {
            smtp_reply(fd,
                "250-KUBU-MTA\r\n"
                "250-SIZE 52428800\r\n"
                "250-PIPELINING\r\n"
                "250-8BITMIME\r\n"
                "250 SMTPUTF8\r\n");
        }
        else if (strncmp(buffer, "MAIL FROM:", 10) == 0)
        {
            smtp_reply(fd, "250 Sender OK\r\n");
        }
        else if (strncmp(buffer, "RCPT TO:", 8) == 0)
        {
            smtp_reply(fd, "250 Recipient OK\r\n");
        }
        else if (strncmp(buffer, "DATA", 4) == 0)
        {
            smtp_reply(fd,
                "354 End data with <CR><LF>.<CR><LF>\r\n");

            while (1)
            {
                memset(buffer, 0, sizeof(buffer));

                n = read(fd, buffer, sizeof(buffer)-1);

                if (n <= 0)
                    break;

                if (strcmp(buffer, ".\r\n") == 0)
                    break;

                printf("%s", buffer);
            }

            smtp_reply(fd, "250 Message queued\r\n");
        }
        else if (strncmp(buffer, "RSET", 4) == 0)
        {
            smtp_reply(fd, "250 Reset OK\r\n");
        }
        else if (strncmp(buffer, "NOOP", 4) == 0)
        {
            smtp_reply(fd, "250 OK\r\n");
        }
        else if (strncmp(buffer, "QUIT", 4) == 0)
        {
            smtp_reply(fd, "221 Bye\r\n");
            break;
        }
        else
        {
            smtp_reply(fd,
                "500 Command not recognized\r\n");
        }
    }

    close(fd);
}
