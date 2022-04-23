#include "GetEntityResource.h"

#include "EntityPool.h"
#include "EntitySerializerFactory.h"

GetEntityResource::GetEntityResource(Project& project) :
    BaseResource(project, "entity/{id: [0-9a-zA-Z-]{36}}", "GET")
{

}

void GetEntityResource::callback(const std::shared_ptr<restbed::Session> session)
{
    const auto request = session->get_request();
    if (request->has_path_parameter("id"))
    {
        auto entity = EntityPool::instance()->find(request->get_path_parameter("id"));
        if (entity)
        {
            auto serializer = EntitySerializerFactory::instance()->getSerializer(entity->type());
            auto jsonObject = serializer->toJson(entity, false);
            session->close(restbed::OK, jsonObject.dump(4));
            return;
        }
    }
    session->close(restbed::BAD_REQUEST);
}
