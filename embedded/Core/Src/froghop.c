#include "main.h"
#include <stdio.h>
#include "froghop_msg.h"
#include "max31865.h"

kettle_data_t kettles[NUM_KETTLES];

void print_kettle_info() {
//	printf("\"ticks\":%lu,", xTaskGetTickCount());
	printf("{\"kettles\":[");
	for (int i = 0; i < NUM_KETTLES; i++) {
		if (i)
			printf(",");
		kettle_data_t *k = &kettles[i];
		printf("{");
		printf("\"id\":%d,", k->id);
		printf("\"setTemp\":%d,", k->setTemp);
		printf("\"currentTemp\":%d,", k->currentTemp);
		printf("\"heaterEnabled\":");
		if (k->heaterEnabled)
			printf("true,");
		else
			printf("false,");

		printf("\"pumpEnabled\":");
		if (k->pumpEnabled)
			printf("true,");
		else
			printf("false,");

		printf("\"heaterOn\":");
		if (k->heaterOn)
			printf("true");
		else
			printf("false");

		printf("}");
	}

	printf("]}\n\r");

}
void read_temps() {
	fh_msg_t msg;
	msg.id = CURRENT_TEMPERATURE;
	msg.kettle_id = HLT; //fix pin names
	msg.value = max31865_get_temperature(HLT_CS_GPIO_Port, HLT_CS_Pin);
	kettles[msg.kettle_id].currentTemp = msg.value;
	xMessageBufferSend(C2G_BufferHandle, (void* ) &msg, sizeof(fh_msg_t), 0);

	fh_msg_t msg2;
	msg2.id = CURRENT_TEMPERATURE;
	msg2.kettle_id = MLT;
	msg2.value = max31865_get_temperature(MLT_CS_GPIO_Port, MLT_CS_Pin);
	kettles[msg2.kettle_id].currentTemp = msg2.value;
	xMessageBufferSend(C2G_BufferHandle, (void* ) &msg2, sizeof(fh_msg_t), 0);

	fh_msg_t msg3;
	msg3.id = CURRENT_TEMPERATURE;
	msg3.kettle_id = BOILER;
	msg3.value = max31865_get_temperature(BOIL_CS_GPIO_Port, BOIL_CS_Pin);
	kettles[msg3.kettle_id].currentTemp = msg3.value;
	xMessageBufferSend(C2G_BufferHandle, (void* ) &msg3, sizeof(fh_msg_t), 0);
}

void temperature_control() {
	fh_msg_t msg;
	msg.id = HEATER_ON;
	for (uint8_t i = 0; i < NUM_KETTLES; i++) {
		msg.kettle_id = i;
		if (kettles[i].heaterEnabled) {
			if (kettles[i].currentTemp < kettles[i].setTemp) {
				kettles[i].heaterOn = 1;
				msg.value = 1;
			} else {
				kettles[i].heaterOn = 0;
				msg.value = 0;
			}
		} else {
			kettles[i].heaterOn = 0;
			msg.value = 0;
		}
		xMessageBufferSend(C2G_BufferHandle, (void* ) &msg, sizeof(fh_msg_t),
				0);
	}
}

void update_gpios() {

	HAL_GPIO_WritePin(HLT_HEATER_GPIO_Port, HLT_HEATER_Pin,
			kettles[HLT].heaterOn);
	HAL_GPIO_WritePin(BOILER_HEATER_GPIO_Port, BOILER_HEATER_Pin,
			kettles[BOILER].heaterOn);

	HAL_GPIO_WritePin(BOILER_PUMP_GPIO_Port, BOILER_PUMP_Pin,
			kettles[BOILER].pumpEnabled);
	HAL_GPIO_WritePin(MLT_PUMP_GPIO_Port, MLT_PUMP_Pin,
			kettles[MLT].pumpEnabled);
	HAL_GPIO_WritePin(HLT_PUMP_GPIO_Port, HLT_PUMP_Pin,
			kettles[HLT].pumpEnabled);
}

void handle_message(fh_msg_t *msg) {
//	printf("Kettle: %d : ", msg->kettle_id);
	if (msg->kettle_id > NUM_KETTLES)
		return;
	switch (msg->id) {
	default:
		printf("No op!\r\n");
		break;
	case HEATER_ENABLE:
//      printf("Heater: %s", msg->value ? "Enabled":"Disabled");
		kettles[msg->kettle_id].heaterEnabled = msg->value ? 1 : 0;
		break;
	case PUMP_ENABLE:
//      printf("Pump: %s\r\n", msg->value ? "on" : "off");
		kettles[msg->kettle_id].pumpEnabled = msg->value ? 1 : 0;
		break;
	case SET_TEMPERATURE:
//      printf("Temperature = %d\r\n", msg->value);
		kettles[msg->kettle_id].setTemp = msg->value;
		break;
	case BUTTON:
      printf("Button =%d\r\n", msg->value);
		break;
	}

}

void Control_Task(void *argument) {
	printf("Control Task start\r\n");
	max31865_init(HLT_CS_GPIO_Port, HLT_CS_Pin);
	max31865_init(MLT_CS_GPIO_Port, MLT_CS_Pin);
	max31865_init(BOIL_CS_GPIO_Port, BOIL_CS_Pin);
	kettles[HLT].id = HLT;
	kettles[MLT].id = MLT;
	kettles[BOILER].id = BOILER;
	while (1) {

		print_kettle_info();
		fh_msg_t msg;
		size_t xReceivedBytes;
		const TickType_t xBlockTime = pdMS_TO_TICKS(1000);

		xReceivedBytes = xMessageBufferReceive(xMessageBuffer, (void* ) &msg,
				sizeof(msg), xBlockTime);

		if (xReceivedBytes > 0) {
			handle_message(&msg);
		}
		temperature_control();
		update_gpios();
		read_temps();
	  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	  HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
	  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
	fh_msg_t msg;
  msg.id = BUTTON;
  msg.kettle_id = 0;
  BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
  switch(GPIO_Pin)
  {
    case BUTTON_RED_Pin:
      msg.value = BUTTON_RIGHT;
      break;
    case BUTTON_BLACK_Pin:
      msg.value = BUTTON_CENTRE;
      break;
    case BUTTON_GREEN_Pin:
      msg.value = BUTTON_LEFT;
      break;
  }
  xMessageBufferSendFromISR(xMessageBuffer, (void *) &msg, sizeof(msg), &pxHigherPriorityTaskWoken);

}
