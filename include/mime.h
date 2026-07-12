// include/mime.h

#ifndef KUBU_MIME_H
#define KUBU_MIME_H

#define MIME_TEXT          1
#define MIME_HTML          2
#define MIME_MULTIPART     3
#define MIME_ATTACHMENT    4

typedef struct
{
    char name[256];
    char value[1024];

} mime_header_t;

typedef struct
{
    int type;

    char content_type[128];

    char encoding[64];

    char filename[256];

    unsigned char *data;

    size_t length;

} mime_part_t;

#endif
