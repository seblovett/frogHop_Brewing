#include <gui/containers/kettle.hpp>

kettle::kettle()
{

}

void kettle::initialize()
{
    kettleBase::initialize();
    // kettleBase::setHeaterChangedCallback(this);
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
    touchgfx_printf("!Set Temp = %d \n", value);
    Unicode::snprintf(textSetTempBuffer, TEXTSETTEMP_SIZE, "%d", value);
    textSetTemp.invalidate();
}
