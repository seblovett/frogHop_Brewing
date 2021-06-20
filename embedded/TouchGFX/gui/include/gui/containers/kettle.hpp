#ifndef KETTLE_HPP
#define KETTLE_HPP

#include <gui_generated/containers/kettleBase.hpp>

class kettle : public kettleBase
{
public:
    kettle();
    virtual ~kettle() {}

    virtual void initialize();
    void setNumber(int no)
    {
        switch (no)
        {
        case 0:
                Unicode::snprintf(kettleNameBuffer, KETTLENAME_SIZE, "HLT");
            break;
        case 1:
                Unicode::snprintf(kettleNameBuffer, KETTLENAME_SIZE, "MLT");
            break;
        case 2:
                Unicode::snprintf(kettleNameBuffer, KETTLENAME_SIZE, "Boiler");
            break;
        
        }
    }
    virtual void actionHeaterChange(bool value);
    virtual void actionPumpChange(bool value);
    void actionSetTempChange(uint8_t value);
protected:
};

#endif // KETTLE_HPP
