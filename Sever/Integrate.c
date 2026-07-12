while (running)
{
    smtp_server_poll(server);

    delivery_scan_queue();
}
