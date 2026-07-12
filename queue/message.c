smtp_message_t msg;

strcpy(msg.sender, session->mail_from);

msg.recipient_count = session->recipient_count;

queue_store(&msg, message_buffer);
