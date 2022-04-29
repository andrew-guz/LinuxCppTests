#ifndef _CONNECTIONINFORMATIONWIDGET_H_
#define _CONNECTIONINFORMATIONWIDGET_H_

#include <Wt/WGroupBox.h>

#include "HttpClientUser.h"
#include "Uuid.h"

class IEntity;

class ConnectionInformationWidget final : public Wt::WGroupBox, public HttpClientUser
{
public:
    ConnectionInformationWidget(const Uuid& id);

    virtual ~ConnectionInformationWidget();

private:
    void dataRequestDone(Wt::AsioWrapper::error_code errorCode, const Wt::Http::Message& message);

private:
    Uuid                _id;
    Wt::WGridLayout*    _gridLayout = nullptr;
    Wt::WLineEdit*      _mainAddress = nullptr;
    Wt::WLineEdit*      _additionalAddress = nullptr;
    Wt::WLineEdit*      _password = nullptr;
};

#endif //_CONNECTIONINFORMATIONWIDGET_H_
