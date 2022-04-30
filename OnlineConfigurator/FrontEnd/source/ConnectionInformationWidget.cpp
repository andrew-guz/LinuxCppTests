#include "ConnectionInformationWidget.h"

#include <nlohmann/json.hpp>

#include "WtGlobal.h"
#include "UrlBuilder.h"
#include "ApplicationErrorNotifier.h"
#include "EntitySerializerFactory.h"
#include "BuildUIHelper.h"

using namespace nlohmann;
using namespace Wt;

ConnectionInformationWidget::ConnectionInformationWidget(const Uuid& id) :
    WGroupBox(u8"Доступ к контроллеру:"),
    EntityGridWidget(id, this)
{
    resize(400, 150);
}
