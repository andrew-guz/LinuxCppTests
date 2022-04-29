#ifndef _BUILDUIHELPER_H_
#define _BUILDUIHELPER_H_

#include "Property.h"

namespace Wt
{
    class WWidget;
    class WGridLayout;
}

class BuildUIHelper final
{
protected:
    BuildUIHelper() = default;

public:
    static Wt::WWidget* createWidget(Wt::WGridLayout* gridLayout, int row, Property& property);
};

#endif //_BUILDUIHELPER_H_
