#include "ev3api.h"
#include "trigger.h"
#include "bluetooth.h"
#include "touchsensor.h"

Bluetooth bluetooth;
TouchSensor touchSensor;

#define START_CMD 1 /* �����[�g�X�^�[�g�p�R�}���h */

void Trigger_init(Trigger* self) {
	//Bluetooth_connect(&bluetooth); /* Bluetooth�ʐM�J�n */


}

void Trigger_wait(Trigger* self) {
	while (1) {
		//TODO:Bluetooth_recv������ƌł܂艺�ւ����Ȃ��Ȃ�
		/*Bluetooth_recv(&bluetooth);
		if (bluetooth.bt_cmd == START_CMD) {
			break;
		}*/

		TouchSensor_check_input(&touchSensor);
		if (touchSensor.input == START_CMD) {
			break;
		}

		tslp_tsk(100);
	}

	ev3_lcd_draw_string("finished", 0, 110);
	fclose(bluetooth.bt_file); /* Bluetooth�ʐM�I�� */
}