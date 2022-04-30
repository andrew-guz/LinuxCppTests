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
    WGroupBox(),
    _id(id)
{
    setTitle(u8"Доступ к контроллеру:");

    resize(400, 150);

    _gridLayout = (WGridLayout*)setLayout(std::make_unique<WGridLayout>());

    registerRequestDoneFunction("data", std::bind(&ConnectionInformationWidget::dataRequestDone, this, std::placeholders::_1, std::placeholders::_2));
    registerRequestDoneFunction("updateField", std::bind(&ConnectionInformationWidget::updateRequestDone, this, std::placeholders::_1, std::placeholders::_2));

    get("data", UrlBuilder::instance()->entityUrl(_id));
}

ConnectionInformationWidget::~ConnectionInformationWidget()
{
    
}

void ConnectionInformationWidget::dataRequestDone(Wt::AsioWrapper::error_code errorCode, const Wt::Http::Message& message)
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

void ConnectionInformationWidget::updateRequestDone(Wt::AsioWrapper::error_code errorCode, const Wt::Http::Message&)
{
    if (errorCode.failed())
    {
        ApplicationErrorNotifier::instance()->notify(u8"Ошибка сетевого взаимодействия");
        return;
    }
}
