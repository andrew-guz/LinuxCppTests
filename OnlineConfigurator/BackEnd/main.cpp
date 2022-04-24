#include <iostream>

#include "Project.h"
#include "GetProjectResource.h"
#include "GetEntityResource.h"
#include "GetPropertyResource.h"
#include "UpdatePropertyResource.h"

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
    service.publish(std::make_shared<GetProjectResource>(project));
    service.publish(std::make_shared<GetEntityResource>(project));
    service.publish(std::make_shared<GetPropertyResource>(project));
    service.publish(std::make_shared<UpdatePropertyResource>(project));
    service.start(settings);

    return 0;
}
