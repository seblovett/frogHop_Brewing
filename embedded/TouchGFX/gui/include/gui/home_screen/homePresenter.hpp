#ifndef HOMEPRESENTER_HPP
#define HOMEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class homeView;

class homePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    homePresenter(homeView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~homePresenter() {};


    void setKettle(kettle_data_t *kettle)
    {
        model->setKettle(kettle);
    }

    void getKettle(kettle_data_t *kettle)
    {
        model->getKettle(kettle);
    }

    void setSelectedKettle(uint8_t kettle)
    {
        model->setSelectedKettle(kettle);
    }

    uint8_t getSelectedKettle()
    {
        return model->getSelectedKettle();
    }

    

private:
    homePresenter();

    homeView& view;
};

#endif // HOMEPRESENTER_HPP
