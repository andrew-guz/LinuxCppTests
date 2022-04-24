#include "GetProjectResource.h"

#include "EntitySerializerFactory.h"

GetProjectResource::GetProjectResource(Project& project) :
    BaseResource(project, "project", "GET")
{

}

void GetProjectResource::callback(const std::shared_ptr<restbed::Session> session)
{
    auto serializer = EntitySerializerFactory::instance()->getSerializer(_project.type());
    auto jsonObject = serializer->toJson(&_project, false);
    session->close(restbed::OK, jsonObject.dump(4));
}
