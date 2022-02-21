#ifndef KETTLE_HPP
#define KETTLE_HPP

#include <gui_generated/containers/kettleBase.hpp>
#ifdef SIMULATOR
#include "gui/model/kettle_data.h"
#else
#include "froghop_msg.h"
#endif

class kettle : public kettleBase
{
public:
    kettle();
    virtual ~kettle() {}

    virtual void initialize();


    int getNumber()
    {
        return selectedKettleID;
    }
    void setNumber(int k)
    {
        // touchgfx_printf("Set kettle to %d\n", k);
        switch (k)
        {
        case HLT:
                Unicode::snprintf(kettleNameBuffer, KETTLENAME_SIZE, "HLT");
            break;
        case MLT:
                Unicode::snprintf(kettleNameBuffer, KETTLENAME_SIZE, "MLT");
            break;
        case BOILER:
                Unicode::snprintf(kettleNameBuffer, KETTLENAME_SIZE, "Boiler");
            break;
        default:
                Unicode::snprintf(kettleNameBuffer, KETTLENAME_SIZE, "Err");
            return; //do not change if we have a bad ID   
        }
        selectedKettleID = k;
        kettleName.invalidate();
    }
    virtual void actionHeaterChange(bool value);
    virtual void actionPumpChange(bool value);
    void actionSetTempChange(int8_t value);
    void getData(kettle_data_t *data);
    void setData(kettle_data_t * data);
    void setCurrentTemp(uint8_t temp);
    void setHeatlines(bool value);
    void setSetTemp(uint8_t temp);
    // void setHeaterToggle(bool value);
    // bool getHeaterToggle();
    // void setPumpToggle(bool value);

protected:
    int selectedKettleID;// = HLT;
    int currentTemp;// = HLT;
    int setTemp;
};

#endif // KETTLE_HPP
