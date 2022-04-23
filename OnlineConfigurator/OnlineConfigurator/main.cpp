#include <iostream>

#include "Project.h"
#include "GetEntityResource.h"

int main()
{
    Project project;

    auto settings = std::make_shared<restbed::Settings>();
    settings->set_port(8080);
    settings->set_default_header("Connection", "close");

    restbed::Service service;
    service.publish(std::make_shared<GetEntityResource>(project));
    service.start(settings);

    return 0;
}
