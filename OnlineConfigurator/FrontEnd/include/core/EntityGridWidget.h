#ifndef _ENTITYGRIDWIDGET_H_
#define _ENTITYGRIDWIDGET_H_

#include <Wt/WContainerWidget.h>

#include "HttpClientUser.h"
#include "Uuid.h"

class IEntity;

class EntityGridWidget : public HttpClientUser
{
public:
    EntityGridWidget(const Uuid& id, Wt::WContainerWidget* parent);

    virtual ~EntityGridWidget() = default;

protected:
    virtual void dataRequestDone(Wt::AsioWrapper::error_code errorCode, const Wt::Http::Message& message);

    virtual void updateRequestDone(Wt::AsioWrapper::error_code errorCode, const Wt::Http::Message& message);

private:
    Wt::WWidget*        _parent = nullptr;
    Wt::WGridLayout*    _gridLayout = nullptr;
    Uuid                _id;
};

#endif //_ENTITYGRIDWIDGET_H_
