smtp_command_t cmd = smtp_parse_command(buffer);

switch(cmd)
{
case CMD_EHLO:
    break;

case CMD_MAIL:
    break;

case CMD_RCPT:
    break;

case CMD_DATA:
    break;

case CMD_QUIT:
    break;

default:
    break;
}
