#include "GetProjectResource.h"

GetProjectResource::GetProjectResource(Project& project) :
    BaseResource(project, "project", "GET")
{

}

void GetProjectResource::callback(const std::shared_ptr<restbed::Session> session)
{

}
