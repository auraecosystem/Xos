The next subsystem is SMTP AUTH, which lets clients authenticate before they’re allowed to relay mail. This is separate from STARTTLS, but in practice it’s typically used after a secure TLS connection is established.

A clean architecture is:

src/
├── auth/
│   ├── auth.c
│   ├── auth.h
│   ├── login.c
│   ├── plain.c
│   ├── cram_md5.c
│   ├── oauth2.c
│   ├── userdb.c
│   └── permissions.c

Authentication Interface

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

⸻

Basic Authentication

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

⸻

SMTP Session

After the client sends:

EHLO localhost

the server advertises:

250-KUBU-MTA
250-PIPELINING
250-SIZE 52428800
250-STARTTLS
250-AUTH PLAIN LOGIN
250 SMTPUTF8

The client can then authenticate:

AUTH LOGIN
334 VXNlcm5hbWU6

Client sends Base64 username:

YWRtaW4=

Server replies:

334 UGFzc3dvcmQ6

Client sends Base64 password:

cGFzc3dvcmQ=

Server:

235 Authentication successful

⸻

Session Structure

typedef struct
{
    int fd;
    int tls_enabled;
    int authenticated;
    char username[256];
} smtp_session_t;

Once authenticated:

session->authenticated = 1;

The server can then allow relaying:

if(session->authenticated)
{
    relay_mail();
}
else
{
    smtp_reply(fd,
        "530 Authentication required\r\n");
}

⸻

Future authentication backends

Instead of hardcoded credentials, KUBU-MTA can support:

* SQLite user database.
* PostgreSQL.
* LDAP / Active Directory.
* OAuth 2.0.
* PAM (Linux Pluggable Authentication Modules).
* JSON Web Tokens (JWT) for API-driven environments.
* Web4 identity providers or other custom identity systems.

At this point, KUBU-MTA would support:

* Receiving SMTP connections.
* Queueing messages.
* Outbound SMTP delivery.
* DNS/MX resolution.
* STARTTLS.
* SMTP AUTH.

The next major subsystem would be MIME processing, enabling proper handling of HTML emails, multipart messages, inline images, and file attachments. That is a key capability for interoperability with modern email clients.
