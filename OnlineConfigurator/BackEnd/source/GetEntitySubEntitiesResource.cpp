#include "GetEntitySubEntitiesResource.h"

#include <iostream>

#include "ResourceHelper.h"
#include "EntitySerializerFactory.h"

GetEntitySubEntitiesResource::GetEntitySubEntitiesResource(Project& project) :
    BaseResource(project, "subEntities/{id: [0-9a-zA-Z-]{36}}", "GET")
{

}

void GetEntitySubEntitiesResource::callback(const std::shared_ptr<restbed::Session> session)
{
    std::cout << "GetEntitySubEntitiesResource: " << session->get_request()->get_path() << std::endl;
    auto entity = ResourceHelper::getEntity(session);
    if (entity)
    {
        auto jsonArray = nlohmann::json::array();
        for (const auto& subEntityName : entity->listSubEntityNames())
        {
            auto jsonObject = nlohmann::json::object();
            jsonObject["name"] = subEntityName;
            jsonObject["id"] = entity->subEntity(subEntityName)->id().data();
            jsonArray.push_back(jsonObject);
        }
        session->close(restbed::OK, jsonArray.dump(4));
        return;
    }
    session->close(restbed::BAD_REQUEST);
}
