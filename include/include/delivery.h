// include/delivery.h

#ifndef KUBU_DELIVERY_H
#define KUBU_DELIVERY_H

void delivery_init(void);
void delivery_scan_queue(void);
void delivery_process_message(const char *path);

#endif
