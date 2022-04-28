#ifndef _CONNECTIONINFORMATIONWIDGET_H_
#define _CONNECTIONINFORMATIONWIDGET_H_

#include <Wt/WGroupBox.h>

#include "Uuid.h"

class ConnectionInformationWidget final : public Wt::WGroupBox
{
public:
    ConnectionInformationWidget(const Uuid& id);

    virtual ~ConnectionInformationWidget();

private:
    Uuid                _id;
    Wt::WGridLayout*    _gridLayout = nullptr;
    Wt::WLineEdit*      _mainAddress = nullptr;
    Wt::WLineEdit*      _additionalAddress = nullptr;
    Wt::WLineEdit*      _password = nullptr;
};

#endif //_CONNECTIONINFORMATIONWIDGET_H_
