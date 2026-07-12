// src/auth.c

#include "auth.h"

#include <string.h>

int auth_init(void)
{
    return 0;
}

int auth_login(smtp_auth_t *auth)
{
    if(strcmp(auth->username,"admin")==0 &&
       strcmp(auth->password,"password")==0)
    {
        auth->authenticated = 1;
        return 0;
    }

    auth->authenticated = 0;

    return -1;
}

int auth_logout(smtp_auth_t *auth)
{
    auth->authenticated = 0;

    return 0;
}
