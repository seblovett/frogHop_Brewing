#include <gui/home_screen/homeView.hpp>
#include <stdio.h>
homeView::homeView()
{

}

void homeView::setupScreen()
{
    homeViewBase::setupScreen();
    recallKettleData();
    uint8_t id = presenter->getSelectedKettle();
    if(id == 0)
    {
        buttonLeft.setVisible(false);
        buttonLeft.invalidate();
    }
    else if (id == NUM_KETTLES - 1)
    {
        buttonRight.setVisible(false);
        buttonRight.invalidate();
    }
}

void homeView::tearDownScreen()
{
    saveKettleData();
    homeViewBase::tearDownScreen();
}

void homeView::printKettle(kettle_data_t *k)
{
    touchgfx_printf("k.id = %d\n", k->id);
    touchgfx_printf("k.setTemp = %d\n", k->setTemp);
    touchgfx_printf("k.currentTemp = %d\n", k->currentTemp);
    touchgfx_printf("k.heaterEnabled = %d\n", k->heaterEnabled);
    touchgfx_printf("k.pumpEnabled = %d\n", k->pumpEnabled);
    touchgfx_printf("k.heaterOn = %d\n", k->heaterOn);
}
void homeView::recallKettleData()
{
    touchgfx_printf("%s\n", __func__);
    kettle_data_t k; 
    k.id = presenter->getSelectedKettle();
    presenter->getKettle(&k);
    printKettle(&k);
    kettle1.setData(&k);
    kettle1.invalidate();
}

void homeView::saveKettleData()
{
    touchgfx_printf("%s\n", __func__);
    kettle_data_t k; 
    k.id = presenter->getSelectedKettle();
    kettle1.getData(&k);
    printKettle(&k);
    presenter->setKettle(&k);
}

void homeView::functionButtonLeft()
{
    saveKettleData(); //save current kettle
    uint8_t id = presenter->getSelectedKettle(); 
    if(id > 0)
    {
        id = id - 1;
        if (id == 0)
        {
            buttonLeft.setVisible(false);
        }
        buttonRight.setVisible(true);
        buttonLeft.invalidate();
        buttonRight.invalidate();
        
        presenter->setSelectedKettle(id);
        recallKettleData();
    }
}

void homeView::functionKettleRight()
{
    saveKettleData(); //save current kettle
    uint8_t id = presenter->getSelectedKettle(); 
    if(id != NUM_KETTLES)
    {
        id = id + 1;
        if (id == NUM_KETTLES-1)
        {
            buttonRight.setVisible(false);
        }
        buttonLeft.setVisible(true);
        buttonLeft.invalidate();
        buttonRight.invalidate();
        
        presenter->setSelectedKettle(id);
        recallKettleData();
    }
}

void homeView::handleTickEvent()
{
#ifdef SIMULATOR
//want to simulate the hardware as this is the entry point for all of the messages from the froghop control task.
static int ticks = 0;

    if((ticks++ % 60) == 0)
    {   
        kettle_data_t k; 
        kettle1.getData(&k);
        printKettle(&k); 
        if(k.heaterEnabled)
        {
            if(k.setTemp > k.currentTemp)
            {
                k.heaterOn = 1;
                if (k.currentTemp < 100)
                {
                    k.currentTemp ++;
                }
            }
            else
            {
                k.heaterOn = 0;
                if(k.currentTemp > 0)
                    k.currentTemp --;
            }
        }
        else
        {
            k.heaterOn = 0;
            if(k.currentTemp > 0)
                k.currentTemp --;
        }

        kettle1.setCurrentTemp(k.currentTemp);
        kettle1.setHeatlines(k.heaterOn? true: false);
    }

#else
    fh_msg_t msg;
    size_t xReceivedBytes;
    
    xReceivedBytes = xMessageBufferReceive( C2G_BufferHandle,
                                            ( void * ) &msg,
                                            sizeof( msg ),
                                            0 );
    if(xReceivedBytes > 0)
    {
        //handle message
        switch (msg.id)
        {
        case CURRENT_TEMPERATURE:
            if(msg.kettle_id == presenter->getSelectedKettle())
                kettle1.setCurrentTemp(msg.value);
            /* code */
            break;

        case HEATER_ON:
            if(msg.kettle_id == presenter->getSelectedKettle())
                kettle1.setHeatlines(msg.value ? true : false);
            break;    
        case BUTTON:
            switch(msg.value)
            {
                case BUTTON_LEFT:
                    functionButtonLeft();
                    break;
                case BUTTON_CENTRE:
                    
                    break;
                case BUTTON_RIGHT:
                    functionKettleRight();
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
        }
    }
#endif
}