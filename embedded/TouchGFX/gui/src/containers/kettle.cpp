#include <gui/containers/kettle.hpp>
#include "froghop_msg.h"

kettle::kettle()
{
    // setNumber(getNumber());
}

void kettle::initialize()
{
    kettleBase::initialize();
}

void kettle::actionHeaterChange(bool value)
{
    fh_msg_t msg; 
    msg.id = HEATER;
    msg.kettle_id = selectedKettleID;
    if (value)
    {
        touchgfx_printf("Heater on\n");
        msg.value = 1;
    }
    else
    {
        msg.value = 0;
        touchgfx_printf("Heater off\n");
    }
    

    xMessageBufferSend( xMessageBuffer,
                                    ( void * ) &msg,
                                    sizeof(fh_msg_t), 0 );

}

void kettle::actionPumpChange(bool value)
{
    fh_msg_t msg; 
    msg.id = PUMP;
    msg.kettle_id = selectedKettleID;
    if (value)
    {
        touchgfx_printf("Pump on\n");
        msg.value = 1;
    }
    else
    {
        msg.value = 0;
        touchgfx_printf("Pump off\n");
    }
    

    xMessageBufferSend( xMessageBuffer,
                                    ( void * ) &msg,
                                    sizeof(fh_msg_t), 0 );
}

void kettle::actionSetTempChange(uint8_t value)
{
    fh_msg_t msg; 
    touchgfx_printf("Set Temp = %d \n", value);
    Unicode::snprintf(textSetTempBuffer, TEXTSETTEMP_SIZE, "%d", value);
    textSetTemp.invalidate();

    msg.id = TEMPERATURE;
    msg.kettle_id = selectedKettleID;
    msg.value = value;
    xMessageBufferSend( xMessageBuffer,
                                    ( void * ) &msg,
                                    sizeof(fh_msg_t), 0 );
}

void kettle::getData(kettle_data_t * data)
{
    if(NULL== data)
        return; 

    data->setTemp = sliderTemperature.getValue();
    data->heaterEnabled = heaterToggle.getState();
    data->pumpEnabled = pumpToggle.getState();
}

void kettle::setData(kettle_data_t * data)
{
    if(NULL== data)
        return; 
    setNumber(data->id);
    sliderTemperature.setValue(data->setTemp);
    heaterToggle.forceState(data->heaterEnabled);
    pumpToggle.forceState(data->pumpEnabled);
}