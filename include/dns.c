// include/dns.h

#ifndef KUBU_DNS_H
#define KUBU_DNS_H

typedef struct
{
    char hostname[256];
    int priority;
} mx_record_t;

int dns_lookup_mx(const char *domain,
                  mx_record_t *records,
                  int max_records);

#endif
