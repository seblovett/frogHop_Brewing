#ifndef SCREENSPLASHVIEW_HPP
#define SCREENSPLASHVIEW_HPP

#include <gui_generated/screensplash_screen/ScreenSplashViewBase.hpp>
#include <gui/screensplash_screen/ScreenSplashPresenter.hpp>

class ScreenSplashView : public ScreenSplashViewBase
{
public:
    ScreenSplashView();
    virtual ~ScreenSplashView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREENSPLASHVIEW_HPP
