// include/parser.h

#ifndef KUBU_PARSER_H
#define KUBU_PARSER_H

typedef enum
{
    CMD_UNKNOWN,

    CMD_HELO,
    CMD_EHLO,

    CMD_MAIL,
    CMD_RCPT,

    CMD_DATA,

    CMD_RSET,
    CMD_NOOP,

    CMD_QUIT

} smtp_command_t;

smtp_command_t smtp_parse_command(const char *line);

#endif
