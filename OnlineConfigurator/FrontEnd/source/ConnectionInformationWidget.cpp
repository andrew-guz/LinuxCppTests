#include "ConnectionInformationWidget.h"

#include <nlohmann/json.hpp>

#include "WtGlobal.h"
#include "UrlBuilder.h"
#include "ApplicationErrorNotifier.h"
#include "EntitySerializerFactory.h"

using namespace nlohmann;
using namespace Wt;

ConnectionInformationWidget::ConnectionInformationWidget(const Uuid& id) :
    WGroupBox(),
    _id(id)
{
    setTitle(u8"Доступ к контроллеру:");

    resize(400, 150);

    _gridLayout = (WGridLayout*)setLayout(std::make_unique<WGridLayout>());

    _gridLayout->addWidget(std::make_unique<WText>(u8"Основной адрес:"), 0, 0);
    _mainAddress = _gridLayout->addWidget(std::make_unique<WLineEdit>(), 0, 1);
    _gridLayout->addWidget(std::make_unique<WText>(u8"Дополнительный адрес:"), 1, 0);
    _additionalAddress = _gridLayout->addWidget(std::make_unique<WLineEdit>(), 1, 1);
    _gridLayout->addWidget(std::make_unique<WText>(u8"Пароль:"), 2, 0);
    _password = _gridLayout->addWidget(std::make_unique<WLineEdit>(), 2, 1);
    _password->setEchoMode(EchoMode::Password);

    registerRequestDoneFunction("data", std::bind(&ConnectionInformationWidget::dataRequestDone, this, std::placeholders::_1, std::placeholders::_2));

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
    
    _mainAddress->setText(entity ? entity->propertyValue("mainAddress").toString() : "");
    _additionalAddress->setText(entity ? entity->propertyValue("additionalAddress").toString() : "");
    _password->setText(entity ? entity->propertyValue("password").toString() : "");
}
