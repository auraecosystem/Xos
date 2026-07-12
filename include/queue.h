// include/queue.h

#ifndef KUBU_QUEUE_H
#define KUBU_QUEUE_H

typedef struct
{
    char id[64];

    char sender[256];

    char recipients[100][256];

    int recipient_count;

    char filename[512];

} smtp_message_t;

int queue_init(void);

int queue_store(smtp_message_t *msg,
                const char *data);

#endif
