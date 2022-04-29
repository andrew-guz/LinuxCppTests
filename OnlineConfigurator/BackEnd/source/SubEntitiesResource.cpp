#include "SubEntitiesResource.h"

#include <iostream>

#include "ResourceHelper.h"
#include "EntitySerializerFactory.h"

SubEntitiesResource::SubEntitiesResource(Project& project) :
    BaseResource(project, "subEntities/{id: [0-9a-zA-Z-]{36}}", { true, false })
{

}

void SubEntitiesResource::callbackGet(const std::shared_ptr<restbed::Session> session)
{
    std::cout << "SubEntitiesResource GET: " << session->get_request()->get_path() << std::endl;
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
        auto jsonObjectString = jsonArray.dump(4);
        std::cout << "SubEntitiesResource GET: " << jsonObjectString << std::endl;
        session->close(restbed::OK, jsonObjectString);
        return;
    }
    session->close(restbed::BAD_REQUEST);
}
