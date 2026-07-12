// src/tls.c

#include "tls.h"

#include <openssl/err.h>
#include <openssl/ssl.h>

int tls_init(void)
{
    SSL_library_init();

    SSL_load_error_strings();

    OpenSSL_add_ssl_algorithms();

    return 0;
}

SSL_CTX *tls_create_server_context(void)
{
    SSL_CTX *ctx =
        SSL_CTX_new(TLS_server_method());

    return ctx;
}

SSL_CTX *tls_create_client_context(void)
{
    SSL_CTX *ctx =
        SSL_CTX_new(TLS_client_method());

    return ctx;
}

SSL *tls_accept(SSL_CTX *ctx,
                int fd)
{
    SSL *ssl = SSL_new(ctx);

    SSL_set_fd(ssl, fd);

    if (SSL_accept(ssl) <= 0)
    {
        SSL_free(ssl);
        return NULL;
    }

    return ssl;
}

SSL *tls_connect(SSL_CTX *ctx,
                 int fd)
{
    SSL *ssl = SSL_new(ctx);

    SSL_set_fd(ssl, fd);

    if (SSL_connect(ssl) <= 0)
    {
        SSL_free(ssl);
        return NULL;
    }

    return ssl;
}

void tls_cleanup(void)
{
    EVP_cleanup();
}
