#include <gui/containers/kettle.hpp>
#ifndef SIMULATOR
#include "froghop_msg.h"


void kettle::actionHeaterChange(bool value)
{
    fh_msg_t msg; 
    msg.id = HEATER_ENABLE;
    msg.kettle_id = selectedKettleID;
    if (value)
    {
        touchgfx_printf("Heater enable\n");
        msg.value = 1;
    }
    else
    {
        msg.value = 0;
        touchgfx_printf("Heater disable\n");
    }
    

    xMessageBufferSend( xMessageBuffer,
                                    ( void * ) &msg,
                                    sizeof(fh_msg_t), 0 );

}

void kettle::actionPumpChange(bool value)
{
    fh_msg_t msg; 
    msg.id = PUMP_ENABLE;
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

    msg.id = SET_TEMPERATURE;
    msg.kettle_id = selectedKettleID;
    msg.value = value;
    xMessageBufferSend( xMessageBuffer,
                                    ( void * ) &msg,
                                    sizeof(fh_msg_t), 0 );
}


#else

void kettle::actionHeaterChange(bool value)
{
    if (value)
    {
        touchgfx_printf("Heater enable\n");
    }
    else
    {
        touchgfx_printf("Heater disable\n");
    }
}

void kettle::actionPumpChange(bool value)
{
    if (value)
    {
        touchgfx_printf("Pump on\n");
    }
    else
    {
        touchgfx_printf("Pump off\n");
    }
    
}

void kettle::actionSetTempChange(uint8_t value)
{
    touchgfx_printf("Set Temp = %d \n", value);
    Unicode::snprintf(textSetTempBuffer, TEXTSETTEMP_SIZE, "%d", value);
    textSetTemp.invalidate();
}

#endif

void kettle::setHeatlines(bool value)
{
    imageHeatlines.setVisible(value);
    imageHeatlines.invalidate();
}

kettle::kettle()
{
    // setNumber(getNumber());
    currentTemp = 0;
}

void kettle::initialize()
{
    kettleBase::initialize();
}


void kettle::getData(kettle_data_t * data)
{
    if(NULL== data)
        return; 
    data->id = selectedKettleID;
    data->setTemp = sliderTemperature.getValue();
    data->currentTemp = currentTemp;
    data->heaterEnabled = heaterToggle.getState();
    data->pumpEnabled = pumpToggle.getState();
    data->heaterOn = imageHeatlines.isVisible();
}

void kettle::setData(kettle_data_t * data)
{
    if(NULL== data)
        return; 
    setNumber(data->id);
    sliderTemperature.setValue(data->setTemp);
    heaterToggle.forceState(data->heaterEnabled);
    pumpToggle.forceState(data->pumpEnabled);
    imageHeatlines.setVisible(data->heaterOn);
    setCurrentTemp(data->currentTemp);
}

void kettle::setCurrentTemp(uint8_t temp)
{
    currentTemp = temp;
    Unicode::snprintf(textCurrentTempBuffer, TEXTCURRENTTEMP_SIZE, "%d", temp);
    textCurrentTemp.invalidate();
}