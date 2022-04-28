#include "Application.h"

#include <Wt/WText.h>

#include "ConnectionInformationWidget.h"

Application::Application(const Wt::WEnvironment& env) :
    Wt::WApplication(env)
{
    setTitle(u8"Онлайн Конфигуратор");

    //root()->addWidget(std::make_unique<ConnectionInformationWidget>());

    registerRequestDoneFunction("project", std::bind(&Application::projectRequestDone, this, std::placeholders::_1, std::placeholders::_2));

    get("project", "http://127.0.0.1:8081/project");
}

void Application::projectRequestDone( Wt::AsioWrapper::error_code errotCode, const Wt::Http::Message& message)
{
    root()->addWidget(std::make_unique<Wt::WText>(message.body()));
}