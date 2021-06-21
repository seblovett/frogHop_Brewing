/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef FRONTENDAPPLICATIONBASE_HPP
#define FRONTENDAPPLICATIONBASE_HPP

#include <mvp/MVPApplication.hpp>
#include <gui/model/Model.hpp>

class FrontendHeap;

class FrontendApplicationBase : public touchgfx::MVPApplication
{
public:
    FrontendApplicationBase(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplicationBase() { }

    // home
    void gotohomeScreenNoTransition();

    void gotohomeScreenSlideTransitionSouth();

    // settings
    void gotosettingsScreenSlideTransitionNorth();

protected:
    touchgfx::Callback<FrontendApplicationBase> transitionCallback;
    FrontendHeap& frontendHeap;
    Model& model;

    // home
    void gotohomeScreenNoTransitionImpl();

    void gotohomeScreenSlideTransitionSouthImpl();

    // settings
    void gotosettingsScreenSlideTransitionNorthImpl();
};

#endif // FRONTENDAPPLICATIONBASE_HPP
