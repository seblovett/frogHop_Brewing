#include <gui/containers/kettle.hpp>

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
    if (value)
        touchgfx_printf("Heater on\n");
    else
        touchgfx_printf("Heater off\n");
}

void kettle::actionPumpChange(bool value)
{
    if (value)
        touchgfx_printf("Pump on\n");
    else
        touchgfx_printf("Pump off\n");
}

void kettle::actionSetTempChange(uint8_t value)
{
    touchgfx_printf("Set Temp = %d \n", value);
    Unicode::snprintf(textSetTempBuffer, TEXTSETTEMP_SIZE, "%d", value);
    textSetTemp.invalidate();
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