#include "EntityGroupBoxWidget.h"

using namespace Wt;

EntityGroupBoxWidget::EntityGroupBoxWidget(const std::string& text, const Uuid& id) :
    WGroupBox(text),
    EntityGridWidget(id, this)
{

}
