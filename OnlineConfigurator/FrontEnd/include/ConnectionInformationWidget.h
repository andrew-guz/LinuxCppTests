#ifndef _CONNECTIONINFORMATIONWIDGET_H_
#define _CONNECTIONINFORMATIONWIDGET_H_

#include <Wt/WGroupBox.h>

#include "EntityGridWidget.h"

class ConnectionInformationWidget final : public Wt::WGroupBox, public EntityGridWidget
{
public:
    ConnectionInformationWidget(const Uuid& id);

    virtual ~ConnectionInformationWidget() = default;
};

#endif //_CONNECTIONINFORMATIONWIDGET_H_
