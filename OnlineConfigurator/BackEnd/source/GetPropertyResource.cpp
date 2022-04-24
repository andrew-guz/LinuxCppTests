#include "GetPropertyResource.h"

#include "ResourceHelper.h"
#include "VariantSerializer.h"

GetPropertyResource::GetPropertyResource(Project& project) :
    BaseResource(project, "entity/{id: [0-9a-zA-Z-]{36}}/{propertyName: .*}", "GET")
{

}

void GetPropertyResource::callback(const std::shared_ptr<restbed::Session> session)
{
    const auto request = session->get_request();
    if (request->has_path_parameter("id") &&
        request->has_path_parameter("propertyName"))
    {
        auto entity = ResourceHelper::getEntity(request);
        if (entity &&
            entity->hasProperty(request->get_path_parameter("propertyName")))
        {
            const auto& property = entity->property(request->get_path_parameter("propertyName"));
            auto jsonObject = VariantSerializer::toJson(property.data());
            session->close(restbed::OK, jsonObject.dump(4));
            return;
        }
    }
    session->close(restbed::BAD_REQUEST);
}