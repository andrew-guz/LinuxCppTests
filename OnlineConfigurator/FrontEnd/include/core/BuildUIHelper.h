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

struct GridPosition
{
    int _row;
    int _column;
    int _rowSpan;
    int _columnSpan;
};

struct UpgradeHelpInfo
{
    Uuid                _entityId;
    std::string         _requestName;
     HttpClientUser*    _httpCLientUser;
};

class BuildUIHelper final
{
protected:
    BuildUIHelper() = default;

public:
    static Wt::WWidget* createTextWidget(Wt::WGridLayout* gridLayout, const Property& property, const GridPosition& gridPosition);

    static Wt::WWidget* createWidget(Wt::WGridLayout* gridLayout, const Property& property, const GridPosition& gridPosition, const UpgradeHelpInfo& upgradeHelpInfo);

    static std::map<std::string, Wt::WWidget*> fillGridLayout(Wt::WGridLayout* gridLayout, const IEntity* entity, const std::string& requestName, HttpClientUser* httpCLientUser);
};

#endif //_BUILDUIHELPER_H_
