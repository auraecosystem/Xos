// include/auth.h

#ifndef KUBU_AUTH_H
#define KUBU_AUTH_H

typedef struct
{
    char username[256];
    char password[256];

    int authenticated;

} smtp_auth_t;

int auth_init(void);

int auth_login(smtp_auth_t *auth);

int auth_logout(smtp_auth_t *auth);

#endif
