// include/smtp_client.h

#ifndef KUBU_SMTP_CLIENT_H
#define KUBU_SMTP_CLIENT_H

typedef struct
{
    char server[256];
    int port;

    char sender[256];
    char recipient[256];

    char message_file[512];

} smtp_client_t;

int smtp_send(smtp_client_t *client);

#endif
