// include/smtp_server.h

#ifndef KUBU_SMTP_SERVER_H
#define KUBU_SMTP_SERVER_H

typedef struct smtp_server smtp_server_t;

smtp_server_t *smtp_server_create(void);

int smtp_server_start(smtp_server_t *);

void smtp_server_poll(smtp_server_t *);

void smtp_server_stop(smtp_server_t *);

void smtp_server_destroy(smtp_server_t *);

#endif
