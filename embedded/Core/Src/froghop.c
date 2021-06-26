#include "main.h"
#include <stdio.h>
#include "froghop_msg.h"


kettle_data_t kettles[NUM_KETTLES];

void read_temps()
{
  fh_msg_t msg; 
  msg.id = CURRENT_TEMPERATURE;
  msg.kettle_id = 0;
  msg.value = kettles[msg.kettle_id].currentTemp++;
  //To Do - read the sensors
  
  xMessageBufferSend( C2G_BufferHandle,
                      ( void * ) &msg,
                      sizeof(fh_msg_t), 0 );
}


void update_gpios()
{

  HAL_GPIO_WritePin(HLT_HEATER_GPIO_Port, HLT_HEATER_Pin, kettles[HLT].heaterOn);
  HAL_GPIO_WritePin(BOILER_HEATER_GPIO_Port, BOILER_HEATER_Pin, kettles[BOILER].heaterOn);

  HAL_GPIO_WritePin(BOILER_PUMP_GPIO_Port, BOILER_PUMP_Pin, kettles[BOILER].pumpEnabled);  
  HAL_GPIO_WritePin(MLT_PUMP_GPIO_Port, MLT_PUMP_Pin, kettles[MLT].pumpEnabled);
  HAL_GPIO_WritePin(HLT_PUMP_GPIO_Port, HLT_PUMP_Pin, kettles[HLT].pumpEnabled);
}

void handle_message(fh_msg_t *msg)
{
  printf("Kettle: %d : ", msg->kettle_id);
  if(msg->kettle_id > NUM_KETTLES)
    return; 
  switch(msg->id)
  {
    default:
      printf("No op!\r\n");
      break;
    case HEATER_ENABLE:
      printf("Heater: %s", msg->value ? "Enabled":"Disabled");
      kettles[msg->kettle_id].heaterEnabled = msg->value ? 1 : 0;
      break;
    case PUMP_ENABLE:
      printf("Pump: %s\r\n", msg->value ? "on" : "off");
      kettles[msg->kettle_id].pumpEnabled = msg->value ? 1 : 0;
      break;
    case SET_TEMPERATURE:
      printf("Temperature = %d\r\n", msg->value);
      kettles[msg->kettle_id].setTemp = msg->value;
      break;
  }

}

void Control_Task(void *argument)
{
	printf("Control Task start\r\n");
	while(1)
	{
		printf("C\r\n");
    fh_msg_t msg;
    size_t xReceivedBytes;
    const TickType_t xBlockTime = pdMS_TO_TICKS( 1000 );
  
    xReceivedBytes = xMessageBufferReceive( xMessageBuffer,
                                            ( void * ) &msg,
                                            sizeof( msg ),
                                            xBlockTime );
 
    if( xReceivedBytes > 0 )
    {    
      handle_message(&msg);
    }
    read_temps();
	}
}