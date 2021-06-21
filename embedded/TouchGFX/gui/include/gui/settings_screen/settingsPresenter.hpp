#ifndef SETTINGSPRESENTER_HPP
#define SETTINGSPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class settingsView;

class settingsPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    settingsPresenter(settingsView& v);

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

    virtual ~settingsPresenter() {};

private:
    settingsPresenter();

    settingsView& view;
};

#endif // SETTINGSPRESENTER_HPP
