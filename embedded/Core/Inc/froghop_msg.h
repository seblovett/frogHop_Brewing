#ifndef __FROGHOP_MSG_H
#define __FROGHOP_MSG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "message_buffer.h"


extern MessageBufferHandle_t xMessageBuffer;

typedef enum {
    NO_OP = 0,
    HEATER = 1,
    PUMP = 2, 
    TEMPERATURE = 3
} fh_msgid_t;

typedef struct {
    fh_msgid_t id;
    uint8_t kettle_id;
    uint8_t value;
} fh_msg_t;

#ifdef __cplusplus
}
#endif

#endif /* __FROGHOP_H */

