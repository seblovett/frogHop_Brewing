#ifndef KETTLE_HPP
#define KETTLE_HPP

#include <gui_generated/containers/kettleBase.hpp>
#include <gui/model/kettle_data.h>


class kettle : public kettleBase
{
public:
    kettle();
    virtual ~kettle() {}

    virtual void initialize();
    enum {
        BOILER = 0,
        MLT = 1,
        HLT = 2,
        NUMB_KETTLES = 3
    };

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
    void actionSetTempChange(uint8_t value);
    void getData(kettle_data_t *data);
    void setData(kettle_data_t * data);

    // void setHeaterToggle(bool value);
    // bool getHeaterToggle();
    // void setPumpToggle(bool value);

protected:
    int selectedKettleID;// = HLT;
};

#endif // KETTLE_HPP
