#include <gui/home_screen/homeView.hpp>

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

void homeView::recallKettleData()
{
    touchgfx_printf("%s\n", __func__);
    kettle_data_t k; 
    k.id = presenter->getSelectedKettle();
    presenter->getKettle(&k);
    touchgfx_printf("k.id = %d\n", k.id);
    touchgfx_printf("k.setTemp = %d\n", k.setTemp);
    touchgfx_printf("k.currentTemp = %d\n", k.currentTemp);
    touchgfx_printf("k.heaterEnabled = %d\n", k.heaterEnabled);
    touchgfx_printf("k.pumpEnabled = %d\n", k.pumpEnabled);
    touchgfx_printf("k.heaterOn = %d\n", k.heaterOn);
    kettle1.setData(&k);
    kettle1.invalidate();
}

void homeView::saveKettleData()
{
    touchgfx_printf("%s\n", __func__);
    kettle_data_t k; 
    k.id = presenter->getSelectedKettle();
    kettle1.getData(&k);
    touchgfx_printf("k.id = %d\n", k.id);
    touchgfx_printf("k.setTemp = %d\n", k.setTemp);
    touchgfx_printf("k.currentTemp = %d\n", k.currentTemp);
    touchgfx_printf("k.heaterEnabled = %d\n", k.heaterEnabled);
    touchgfx_printf("k.pumpEnabled = %d\n", k.pumpEnabled);
    touchgfx_printf("k.heaterOn = %d\n", k.heaterOn);
    presenter->setKettle(&k);
}

void homeView::functionButtonLeft()
{
    saveKettleData(); //save current kettle
    uint8_t id = presenter->getSelectedKettle(); 
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

void homeView::functionKettleRight()
{
    saveKettleData(); //save current kettle
    uint8_t id = presenter->getSelectedKettle(); 
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
