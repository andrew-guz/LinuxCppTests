#ifndef _BUILDUIHELPER_H_
#define _BUILDUIHELPER_H_

#include <map>
#include <string>

#include "IEntity.h"
#include "Uuid.h"
#include "HttpClientUser.h"
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
    static Wt::WWidget* createWidget(Wt::WGridLayout* gridLayout, int row, const Property& property, const Uuid& entityId, const std::string& requestName, HttpClientUser* httpCLientUser);

    static std::map<std::string, Wt::WWidget*> fillGridLayout(Wt::WGridLayout* gridLayout, const IEntity* entity, const std::string& requestName, HttpClientUser* httpCLientUser);
};

#endif //_BUILDUIHELPER_H_
