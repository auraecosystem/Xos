// src/parser.c

#include <string.h>

#include "parser.h"

smtp_command_t smtp_parse_command(const char *line)
{
    if (!strncmp(line,"HELO",4))
        return CMD_HELO;

    if (!strncmp(line,"EHLO",4))
        return CMD_EHLO;

    if (!strncmp(line,"MAIL FROM:",10))
        return CMD_MAIL;

    if (!strncmp(line,"RCPT TO:",8))
        return CMD_RCPT;

    if (!strncmp(line,"DATA",4))
        return CMD_DATA;

    if (!strncmp(line,"RSET",4))
        return CMD_RSET;

    if (!strncmp(line,"NOOP",4))
        return CMD_NOOP;

    if (!strncmp(line,"QUIT",4))
        return CMD_QUIT;

    return CMD_UNKNOWN;
}
