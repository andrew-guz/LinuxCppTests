#include "EntityResource.h"

#include <iostream>

#include "ResourceHelper.h"
#include "EntitySerializerFactory.h"

EntityResource::EntityResource(Project& project) :
    BaseResource(project, "entity/{id: [0-9a-zA-Z-]{36}}", { true, false, false, false })
{

}

void EntityResource::callbackGet(const std::shared_ptr<restbed::Session> session)
{
    std::cout << "EntityResource GET: " << session->get_request()->get_path() << std::endl;
    auto entity = ResourceHelper::getEntity(session);
    if (entity)
    {
        auto serializer = EntitySerializerFactory::instance()->getSerializer(entity->type());
        auto jsonObject = serializer->toJson(entity, false);
        auto jsonObjectString = jsonObject.dump(4);
        std::cout << "EntityResource GET: " << jsonObjectString << std::endl;
        session->close(restbed::OK, jsonObjectString);
        return;
    }
    session->close(restbed::BAD_REQUEST);
}
