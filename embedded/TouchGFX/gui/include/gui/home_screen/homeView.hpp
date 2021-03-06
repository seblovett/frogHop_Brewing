#ifndef HOMEVIEW_HPP
#define HOMEVIEW_HPP

#include <gui_generated/home_screen/homeViewBase.hpp>
#include <gui/home_screen/homePresenter.hpp>
#include <gui/containers/kettle.hpp>

class homeView : public homeViewBase
{
public:
    homeView();
    virtual ~homeView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void functionButtonLeft();
    virtual void functionKettleRight();
    void recallKettleData();
    void saveKettleData();
    virtual void handleTickEvent();
    void printKettle(kettle_data_t *k);
protected:
};

#endif // HOMEVIEW_HPP
