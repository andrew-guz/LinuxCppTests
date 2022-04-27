#include "Application.h"

#include "ConnectionInformationWidget.h"

Application::Application(const Wt::WEnvironment& env) :
    Wt::WApplication(env)
{
    setTitle(u8"Онлайн Конфигуратор");

    root()->addWidget(std::make_unique<ConnectionInformationWidget>());
}
