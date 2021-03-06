#include "PropertyResource.h"

#include <iostream>

#include "ResourceHelper.h"
#include "VariantSerializer.h"

PropertyResource::PropertyResource(Project& project) :
    BaseResource(project, "property/{id: [0-9a-zA-Z-]{36}}/{propertyName: .*}", { true, false, true, false })
{

}

void PropertyResource::callbackGet(const std::shared_ptr<restbed::Session> session)
{
    const auto request = session->get_request();
    std::cout << "PropertyResource GET: " << request->get_path() << std::endl;
    if (request->has_path_parameter("id") &&
        request->has_path_parameter("propertyName"))
    {
        auto entity = ResourceHelper::getEntity(request);
        if (entity &&
            entity->hasProperty(request->get_path_parameter("propertyName")))
        {
            const auto& property = entity->property(request->get_path_parameter("propertyName"));
            auto jsonObject = VariantSerializer::toJson(property.data());
            auto jsonObjectString = jsonObject.dump(4);
            std::cout << "PropertyResource GET: " << jsonObjectString << std::endl;
            session->close(restbed::OK, jsonObjectString);
            return;
        }
    }
    session->close(restbed::BAD_REQUEST);
}

void PropertyResource::callbackPut(const std::shared_ptr<restbed::Session> session)
{
    const auto request = session->get_request();
    std::cout << "PropertyResource PUT: " << request->get_path() << std::endl;
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
                std::cout << "PropertyResource PUT: done" << std::endl;
                session->close(restbed::OK);
            }
        }
    }
    session->close(restbed::BAD_REQUEST);
}
