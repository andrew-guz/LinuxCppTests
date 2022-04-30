#include "EntityGridWidget.h"

#include "WtGlobal.h"
#include "UrlBuilder.h"
#include "ApplicationErrorNotifier.h"
#include "EntitySerializerFactory.h"
#include "BuildUIHelper.h"

using namespace nlohmann;
using namespace Wt;

EntityGridWidget::EntityGridWidget(const Uuid& id, WContainerWidget* parent) :
    _id(id)
{
    _gridLayout = (WGridLayout*)parent->setLayout(std::make_unique<WGridLayout>());

    registerRequestDoneFunction("data", std::bind(&EntityGridWidget::dataRequestDone, this, std::placeholders::_1, std::placeholders::_2));
    registerRequestDoneFunction("updateField", std::bind(&EntityGridWidget::updateRequestDone, this, std::placeholders::_1, std::placeholders::_2));

    get("data", UrlBuilder::instance()->entityUrl(_id));
}

void EntityGridWidget::dataRequestDone(AsioWrapper::error_code errorCode, const Http::Message& message)
{
    if (errorCode.failed() ||
        message.body().empty())
    {
        ApplicationErrorNotifier::instance()->notify(u8"Ошибка сетевого взаимодействия");
        return;
    }

    auto json = json::parse(message.body());
    auto entity = EntitySerializerFactory::instance()->getSerializer("connectionInformation")->toEntitySharedPtr(json);
    
    BuildUIHelper::fillGridLayout(_gridLayout, entity.get(), "updateField", this);
}

void EntityGridWidget::updateRequestDone(AsioWrapper::error_code errorCode, const Http::Message& message)
{
    if (errorCode.failed())
    {
        ApplicationErrorNotifier::instance()->notify(u8"Ошибка сетевого взаимодействия");
        return;
    }
}
