// include/tls.h

#ifndef KUBU_TLS_H
#define KUBU_TLS_H

#include <openssl/ssl.h>

typedef struct
{
    SSL_CTX *ctx;
    SSL *ssl;

} kubu_tls_t;

int tls_init(void);

SSL_CTX *tls_create_server_context(void);

SSL_CTX *tls_create_client_context(void);

SSL *tls_accept(SSL_CTX *ctx,
                int socket_fd);

SSL *tls_connect(SSL_CTX *ctx,
                 int socket_fd);

void tls_cleanup(void);

#endif
