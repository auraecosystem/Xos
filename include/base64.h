// include/base64.h

#ifndef KUBU_BASE64_H
#define KUBU_BASE64_H

int base64_encode(
    const unsigned char *input,
    int length,
    char *output);

int base64_decode(
    const char *input,
    unsigned char *output);

#endif
