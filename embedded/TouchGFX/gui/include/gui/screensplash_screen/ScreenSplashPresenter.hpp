#ifndef SCREENSPLASHPRESENTER_HPP
#define SCREENSPLASHPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScreenSplashView;

class ScreenSplashPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScreenSplashPresenter(ScreenSplashView& v);

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

    virtual ~ScreenSplashPresenter() {};

private:
    ScreenSplashPresenter();

    ScreenSplashView& view;
};

#endif // SCREENSPLASHPRESENTER_HPP
