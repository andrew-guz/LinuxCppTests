#include "Application.h"

#include <nlohmann/json.hpp>

#include "WtGlobal.h"
#include "UrlBuilder.h"
#include "ApplicationErrorNotifier.h"
#include "EntityGroupBoxWidget.h"

using namespace nlohmann;
using namespace Wt;

Application::Application(const WEnvironment& env) :
    WApplication(env)
{
    setTitle(u8"Онлайн Конфигуратор");

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
            auto connectionInformationWidget = root()->addWidget(std::make_unique<EntityGroupBoxWidget>(u8"Доступ к контроллеру:", id));
            connectionInformationWidget->resize(500, 150);
        }
        else if(subEntityJson["name"].get<std::string>() == "errorProcessing")
        {
            auto errorProcessingWidget = root()->addWidget(std::make_unique<EntityGroupBoxWidget>(u8"Обработка ошибок:", id));
            errorProcessingWidget->resize(700, 200);
        }
    }
}