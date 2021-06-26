#ifndef KETTLE_DATA_H
#define KETTLE_DATA_H

#define BOILER 0
#define MLT 1
#define HLT 2
#define NUM_KETTLES 3
typedef enum {
    NO_OP = 0,
    HEATER_ENABLE = 1,
    HEATER_ON = 2,
    PUMP_ENABLE = 3, 
    SET_TEMPERATURE = 4,
    CURRENT_TEMPERATURE = 5
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

#endif