#ifndef KETTLESVIEW_HPP
#define KETTLESVIEW_HPP

#include <gui_generated/kettles_screen/kettlesViewBase.hpp>
#include <gui/kettles_screen/kettlesPresenter.hpp>

class kettlesView : public kettlesViewBase
{
public:
    kettlesView();
    virtual ~kettlesView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
     void setNumber(int no)
    {
        Unicode::itoa(no, textBuffer, TEXT_SIZE, 10);
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
protected:
};

#endif // KETTLESVIEW_HPP
