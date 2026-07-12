// include/session.h

#ifndef KUBU_SESSION_H
#define KUBU_SESSION_H

typedef enum
{
    SMTP_STATE_CONNECT = 0,
    SMTP_STATE_GREET,
    SMTP_STATE_MAIL,
    SMTP_STATE_RCPT,
    SMTP_STATE_DATA,
    SMTP_STATE_QUIT
} smtp_state_t;

typedef struct
{
    int fd;

    smtp_state_t state;

    char helo[256];

    char mail_from[256];

    char recipients[100][256];

    int recipient_count;

} smtp_session_t;

void smtp_session_run(smtp_session_t *session);

#endif
