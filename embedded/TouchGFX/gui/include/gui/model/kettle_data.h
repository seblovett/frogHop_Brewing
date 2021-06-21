#ifndef KETTLE_DATA_H
#define KETTLE_DATA_H

#define NUM_KETTLES 3

typedef struct {
    uint8_t id;
    uint8_t setTemp;
    uint8_t currentTemp;
    bool heaterEnabled;
    bool pumpEnabled;
    bool heaterOn;
    
} kettle_data_t;

#endif