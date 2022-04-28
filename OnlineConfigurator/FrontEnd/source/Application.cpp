#include "Application.h"

#include <nlohmann/json.hpp>
#include <Wt/WText.h>

#include "ConnectionInformationWidget.h"

using namespace nlohmann;
using namespace Wt;

Application::Application(const WEnvironment& env) :
    WApplication(env)
{
    setTitle(u8"Онлайн Конфигуратор");

    //root()->addWidget(std::make_unique<ConnectionInformationWidget>());

    registerRequestDoneFunction("project", std::bind(&Application::projectRequestDone, this, std::placeholders::_1, std::placeholders::_2));
    registerRequestDoneFunction("projectSubEntities", std::bind(&Application::projectSubEntitiesRequestDone, this, std::placeholders::_1, std::placeholders::_2));

    get("project", "http://127.0.0.1:8081/project");
}

void Application::projectRequestDone(AsioWrapper::error_code errotCode, const Http::Message& message)
{
    root()->addWidget(std::make_unique<Wt::WText>(message.body()));
    
    auto json = json::parse(message.body());

    get("projectSubEntities", std::string("http://127.0.0.1:8081/subEntities/") + json["id"].get<std::string>());
}

void Application::projectSubEntitiesRequestDone(AsioWrapper::error_code errotCode, const Http::Message& message)
{
    root()->addWidget(std::make_unique<Wt::WText>(message.body()));   
}