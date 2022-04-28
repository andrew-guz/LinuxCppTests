#include "Application.h"

#include <nlohmann/json.hpp>
#include <Wt/WEnvironment.h>
#include <Wt/WText.h>

#include "UrlBuilder.h"
#include "ApplicationErrorNotifier.h"
#include "ConnectionInformationWidget.h"

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
    if (errorCode.failed())
    {
        ApplicationErrorNotifier::instance()->notify(u8"Ошибка сетевого взаимодействия");
        return;
    }

    //root()->addWidget(std::make_unique<Wt::WText>(message.body()));
    
    auto json = json::parse(message.body());
    auto id = json["id"].get<std::string>();
    auto url = UrlBuilder::instance()->subEntitiesUrl(id);
    wApp->log(url);
    get("projectSubEntities", url);
}

void Application::projectSubEntitiesRequestDone(AsioWrapper::error_code errorCode, const Http::Message& message)
{
    if (errorCode.failed())
    {
        ApplicationErrorNotifier::instance()->notify(u8"Ошибка сетевого взаимодействия");
        return;
    }

    //root()->addWidget(std::make_unique<Wt::WText>(message.body()));   

    auto json = json::parse(message.body());
    for (auto iter = json.begin(); iter != json.end(); ++iter)
    {
        auto subEntityJson = *iter;
        if (subEntityJson["name"].get<std::string>() == "connectionInformation")
        {
            auto id = Uuid(subEntityJson["id"].get<std::string>());
            root()->addWidget(std::make_unique<ConnectionInformationWidget>(id));
        }
    }
}