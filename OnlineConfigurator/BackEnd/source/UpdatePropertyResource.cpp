#include "UpdatePropertyResource.h"

#include <iostream>

#include "ResourceHelper.h"
#include "VariantSerializer.h"

UpdatePropertyResource::UpdatePropertyResource(Project& project) :
    BaseResource(project, "property/{id: [0-9a-zA-Z-]{36}}/{propertyName: .*}", "PUT")
{

}

void UpdatePropertyResource::callback(const std::shared_ptr<restbed::Session> session)
{
    const auto request = session->get_request();
    std::cout << "UpdatePropertyResource: " << request->get_path() << std::endl;
    if (request->has_path_parameter("id") &&
        request->has_path_parameter("propertyName"))
    {
        auto entity = ResourceHelper::getEntity(request);
        if (entity &&
            entity->hasProperty(request->get_path_parameter("propertyName")))
        {
            auto jsonObject = ResourceHelper::getBodyJson(session);
            if (!jsonObject.empty())
            {
                auto propertyName = request->get_path_parameter("propertyName");
                auto data = VariantSerializer::fromJson(jsonObject);
                entity->property(propertyName) = data;
                session->close(restbed::OK);
            }
        }
    }
    session->close(restbed::BAD_REQUEST);
}