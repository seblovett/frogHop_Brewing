#ifndef MODEL_HPP
#define MODEL_HPP

#include <touchgfx/hal/types.hpp>
#include <gui/model/kettle_data.h>


class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    void setSelectedKettle(uint8_t id)
    {
        selectedKettle = id;
    }
    uint8_t getSelectedKettle()
    {
        return selectedKettle;
    }

    void setKettle(kettle_data_t *k)
    {
        if(NULL == k)
            return;
        
        if(k->id > NUM_KETTLES)
            return; 
        
        // kettles[k->id].id = k->id;
        kettles[k->id].setTemp = k->setTemp;
        kettles[k->id].currentTemp = k->currentTemp;
        kettles[k->id].heaterEnabled = k->heaterEnabled;
        kettles[k->id].pumpEnabled = k->pumpEnabled;
        kettles[k->id].heaterOn = k->heaterOn;
    }

    void getKettle(kettle_data_t *k)
    {
        if(NULL == k)
            return;
        if(k->id > NUM_KETTLES)
            return; 
        
        // k->id = kettles[k->id].id;
        k->setTemp = kettles[k->id].setTemp;
        k->currentTemp = kettles[k->id].currentTemp;
        k->heaterEnabled = kettles[k->id].heaterEnabled;
        k->pumpEnabled = kettles[k->id].pumpEnabled;
        k->heaterOn = kettles[k->id].heaterOn;
    
    }

protected:
    ModelListener* modelListener;

    uint8_t selectedKettle;

    kettle_data_t kettles[NUM_KETTLES];

};

#endif // MODEL_HPP
