#include "GetEntityResource.h"

#include "ResourceHelper.h"
#include "EntitySerializerFactory.h"

GetEntityResource::GetEntityResource(Project& project) :
    BaseResource(project, "entity/{id: [0-9a-zA-Z-]{36}}", "GET")
{

}

void GetEntityResource::callback(const std::shared_ptr<restbed::Session> session)
{
    auto entity = ResourceHelper::getEntity(session);
    if (entity)
    {
        auto serializer = EntitySerializerFactory::instance()->getSerializer(entity->type());
        auto jsonObject = serializer->toJson(entity, false);
        session->close(restbed::OK, jsonObject.dump(4));
        return;
    }
    session->close(restbed::BAD_REQUEST);
}
