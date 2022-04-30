#include "Application.h"

#include <nlohmann/json.hpp>

#include "WtGlobal.h"
#include "UrlBuilder.h"
#include "ApplicationErrorNotifier.h"
#include "BuildUIHelper.h"
#include "EntityGroupBoxWidget.h"

using namespace nlohmann;
using namespace Wt;

Application::Application(const WEnvironment& env) :
    WApplication(env)
{
    setTitle(u8"Онлайн Конфигуратор");

    _gridLayout = (WGridLayout*)root()->setLayout(std::make_unique<WGridLayout>());

    registerRequestDoneFunction("project", std::bind(&Application::projectRequestDone, this, std::placeholders::_1, std::placeholders::_2));
    registerRequestDoneFunction("projectSubEntities", std::bind(&Application::projectSubEntitiesRequestDone, this, std::placeholders::_1, std::placeholders::_2));

    get("project", UrlBuilder::instance()->projectUrl());
}

void Application::projectRequestDone(AsioWrapper::error_code errorCode, const Http::Message& message)
{
    if (errorCode.failed() ||
        message.body().empty())
    {
        ApplicationErrorNotifier::instance()->notify(u8"Ошибка сетевого взаимодействия");
        return;
    }
    
    auto json = json::parse(message.body());
    auto id = json["id"].get<std::string>();
    auto url = UrlBuilder::instance()->subEntitiesUrl(id);
    wApp->log(url);
    get("projectSubEntities", url);
}

void Application::projectSubEntitiesRequestDone(AsioWrapper::error_code errorCode, const Http::Message& message)
{
    if (errorCode.failed() ||
        message.body().empty())
    {
        ApplicationErrorNotifier::instance()->notify(u8"Ошибка сетевого взаимодействия");
        return;
    }

    auto json = json::parse(message.body());
    for (auto iter = json.begin(); iter != json.end(); ++iter)
    {
        auto subEntityJson = *iter;
        auto id = Uuid(subEntityJson["id"].get<std::string>());
        if (subEntityJson["name"].get<std::string>() == "connectionInformation")
        {
            auto connectionInformationWidget = _gridLayout->addWidget(std::make_unique<EntityGroupBoxWidget>(u8"Доступ к контроллеру:", id), 1, 0, 1, 2);
            connectionInformationWidget->resize(700, 150);
        }
        else if(subEntityJson["name"].get<std::string>() == "errorProcessing")
        {
            auto errorProcessingWidget = _gridLayout->addWidget(std::make_unique<EntityGroupBoxWidget>(u8"Обработка ошибок:", id), 2, 1, 1, 1);
            errorProcessingWidget->resize(500, 200);
        }
    }
}