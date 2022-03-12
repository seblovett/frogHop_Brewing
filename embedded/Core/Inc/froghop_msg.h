#ifndef __FROGHOP_MSG_H
#define __FROGHOP_MSG_H

#ifdef __cplusplus
extern "C" {
#endif
#include "cmsis_os.h"
#include "message_buffer.h"


extern MessageBufferHandle_t xMessageBuffer;
extern MessageBufferHandle_t C2G_BufferHandle;

#define BOILER 0
#define MLT 1
#define HLT 2
#define NUM_KETTLES 3

#define BUTTON_TOP    1
#define BUTTON_MIDDLE  2
#define BUTTON_BOTTOM   3
#define BUTTON_ROTARY	4
#define ROTARY_CW		5
#define ROTARY_ACW		6

typedef enum {
    NO_OP = 0,
    HEATER_ENABLE = 1,
    HEATER_ON = 2,
    PUMP_ENABLE = 3, 
    SET_TEMPERATURE = 4,
    CURRENT_TEMPERATURE = 5,
    BUTTON = 6
} fh_msgid_t;

typedef struct {
    fh_msgid_t id;
    uint8_t kettle_id;
    uint8_t value;
} fh_msg_t;

typedef struct {
    uint8_t id;
    uint8_t setTemp;
    uint8_t currentTemp;
    uint8_t heaterEnabled;
    uint8_t pumpEnabled;
    uint8_t heaterOn;
    
} kettle_data_t;


#ifdef __cplusplus
}
#endif

#endif /* __FROGHOP_H */

