220 KUBU-MTA ESMTP Ready
EHLO localhost
250-KUBU-MTA
250-SIZE 52428800
250-PIPELINING
250-8BITMIME
250 SMTPUTF8
MAIL FROM:<alice@example.com>
250 Sender OK
RCPT TO:<bob@example.com>
250 Recipient OK
DATA
354 End data with <CR><LF>.<CR><LF>
Subject: Test

Hello World!
.
250 Message queued
QUIT
221 Bye
