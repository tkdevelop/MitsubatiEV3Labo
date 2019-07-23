#ifndef _START_H_
#define _START_H_

void Start_init();
void Start_wait();
void Start_start();
void Start_bt_connect();
void Start_bt_recv_task(intptr_t unused);
void Start_bt_close();

#endif