// src/main.c

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "config.h"
#include "logger.h"
#include "smtp_server.h"

static volatile int running = 1;

static void signal_handler(int sig)
{
    (void)sig;
    running = 0;
}

int main(int argc, char *argv[])
{
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    logger_init();

    if (config_load("config/kubu-mta.conf") != 0)
    {
        logger_error("Failed to load configuration.");
        return EXIT_FAILURE;
    }

    smtp_server_t *server = smtp_server_create();

    if (!server)
    {
        logger_error("Unable to create SMTP server.");
        return EXIT_FAILURE;
    }

    if (smtp_server_start(server) != 0)
    {
        logger_error("Unable to start SMTP server.");
        smtp_server_destroy(server);
        return EXIT_FAILURE;
    }

    logger_info("KUBU-MTA started.");

    while (running)
    {
        smtp_server_poll(server);
    }

    logger_info("Stopping...");

    smtp_server_stop(server);
    smtp_server_destroy(server);

    logger_shutdown();

    return EXIT_SUCCESS;
}
