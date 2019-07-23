#ifndef _TRIGGER_H_
#define _TRIGGER_H_

typedef struct {
	
}Trigger;
void Trigger_init(Trigger* self);
void Trigger_wait(Trigger* self);
void Trigger_bt_connect();
void Trigger_bt_recv_task(intptr_t unused);
void Trigger_bt_close();

#endif