#ifndef _ENTITYGROUPBOXWIDGET_H_
#define _ENTITYGROUPBOXWIDGET_H_

#include <Wt/WGroupBox.h>

#include "EntityGridWidget.h"

class EntityGroupBoxWidget final : public Wt::WGroupBox, public EntityGridWidget
{
public:
    EntityGroupBoxWidget(const std::string& text, const Uuid& id);

    virtual ~EntityGroupBoxWidget() = default;
};

#endif //_ENTITYGROUPBOXWIDGET_H_
