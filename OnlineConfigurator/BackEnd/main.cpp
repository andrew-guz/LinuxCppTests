#include <iostream>

#include "Project.h"
#include "GetProjectResource.h"
#include "GetEntityResource.h"
#include "GetPropertyResource.h"
#include "UpdatePropertyResource.h"

int main()
{
    Project project;

    auto settings = std::make_shared<restbed::Settings>();
    settings->set_port(8080);
    settings->set_default_header("Connection", "close");

    restbed::Service service;
    service.publish(std::make_shared<GetProjectResource>(project));
    service.publish(std::make_shared<GetEntityResource>(project));
    service.publish(std::make_shared<GetPropertyResource>(project));
    service.publish(std::make_shared<UpdatePropertyResource>(project));
    service.start(settings);

    return 0;
}
