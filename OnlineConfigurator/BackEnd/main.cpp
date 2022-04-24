#include <iostream>

#include "Project.h"
#include "ProjectResource.h"
#include "EntityResource.h"
#include "SubEntitiesResource.h"
#include "PropertyResource.h"

int main(int argc, char* argv[])
{    
    if (argc < 2)
        return -1;
    auto portStr = argv[1];
    int port = -1;
    try
    {
        port = atoi(portStr);        
    }
    catch(...)
    {
        return -1;
    }   

    Project project;

    auto settings = std::make_shared<restbed::Settings>();
    settings->set_port(port);
    settings->set_default_header("Connection", "close");

    restbed::Service service;
    service.publish(std::make_shared<ProjectResource>(project));
    service.publish(std::make_shared<EntityResource>(project));
    service.publish(std::make_shared<SubEntitiesResource>(project));
    service.publish(std::make_shared<PropertyResource>(project));
    service.start(settings);

    return 0;
}
