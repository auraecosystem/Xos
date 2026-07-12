mx_record_t mx[10];

int count = dns_lookup_mx("example.com",
                          mx,
                          10);

if (count > 0)
{
    printf("MX: %s\n",
           mx[0].hostname);

    strcpy(client.server,
           mx[0].hostname);

    smtp_send(&client);
}
