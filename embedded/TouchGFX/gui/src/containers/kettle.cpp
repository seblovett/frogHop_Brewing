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

void kettle::actionSetTempChange(int8_t value)
{
    fh_msg_t msg; 
    int newSetTemp = setTemp + value;
//    setTemp += value;
    if(newSetTemp > 100)
    	newSetTemp = 100;
    if (newSetTemp < 0)
    	newSetTemp = 0;

    setSetTemp(newSetTemp);

    msg.id = SET_TEMPERATURE;
    msg.kettle_id = selectedKettleID;
    msg.value = (uint8_t)setTemp;
    xMessageBufferSend( xMessageBuffer,
                                    ( void * ) &msg,
                                    sizeof(fh_msg_t), 0 );
}

void kettle::incrementSetTemp()
{
        fh_msg_t msg; 
    int newSetTemp = setTemp + 1;
//    setTemp += value;
    if(newSetTemp > 100)
    	newSetTemp = 100;
    if (newSetTemp < 0)
    	newSetTemp = 0;

    setSetTemp(newSetTemp);

    msg.id = SET_TEMPERATURE;
    msg.kettle_id = selectedKettleID;
    msg.value = (uint8_t)setTemp;
    xMessageBufferSend( xMessageBuffer,
                                    ( void * ) &msg,
                                    sizeof(fh_msg_t), 0 );
}

void kettle::decrementSetTemp()
{
        fh_msg_t msg; 
    int newSetTemp = setTemp - 1;
//    setTemp += value;
    if(newSetTemp > 100)
    	newSetTemp = 100;
    if (newSetTemp < 0)
    	newSetTemp = 0;

    setSetTemp(newSetTemp);

    msg.id = SET_TEMPERATURE;
    msg.kettle_id = selectedKettleID;
    msg.value = (uint8_t)setTemp;
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

void kettle::actionSetTempChange(int8_t value)
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
    data->setTemp = setTemp;
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
    heaterToggle.forceState(data->heaterEnabled);
    pumpToggle.forceState(data->pumpEnabled);
    imageHeatlines.setVisible(data->heaterOn);
    setCurrentTemp(data->currentTemp);
    setSetTemp(data->setTemp);
}

void kettle::setCurrentTemp(uint8_t temp)
{
    currentTemp = temp;
    Unicode::snprintf(textCurrentTempBuffer, TEXTCURRENTTEMP_SIZE, "%d", temp);
    textCurrentTemp.invalidate();
}

void kettle::setSetTemp(uint8_t temp)
{
	touchgfx_printf("Set Temp = %d \n", temp);
	setTemp = temp;
	Unicode::snprintf(textSetTempBuffer, TEXTSETTEMP_SIZE, "%d", setTemp);
	textSetTemp.invalidate();
}
