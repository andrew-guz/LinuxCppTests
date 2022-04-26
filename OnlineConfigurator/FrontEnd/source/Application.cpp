#include "Application.h"

#include "BackEndRequest.h"
#include "ConnectionInformationWidget.h"

Application::Application(const Wt::WEnvironment& env) :
    Wt::WApplication(env)
{
    setTitle(u8"Онлайн Конфигуратор");

    auto br = new BackEndRequest();
    br->get("http://127.0.0.1:8081/project", "test...");

    root()->addWidget(std::make_unique<ConnectionInformationWidget>());
}
