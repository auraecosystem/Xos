// src/dns.c

#include "dns.h"

#include <stdio.h>
#include <string.h>

int dns_lookup_mx(const char *domain,
                  mx_record_t *records,
                  int max_records)
{
    if (max_records < 1)
        return 0;

    /* Placeholder */
    snprintf(records[0].hostname,
             sizeof(records[0].hostname),
             "mail.%s",
             domain);

    records[0].priority = 10;

    return 1;
}
