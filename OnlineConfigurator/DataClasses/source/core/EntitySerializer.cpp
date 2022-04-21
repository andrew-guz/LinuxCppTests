#include "EntitySerializer.h"

std::string EntitySerializer::toString(const IEntity* entity) const
{
    return toJson(entity).dump();
}

IEntity* EntitySerializer::toEntity(const std::string& str) const
{
    auto jsonObject = nlohmann::json::parse(str);
    auto type = jsonObject["type"].get<std::string>();
    auto id = jsonObject["type"].get<std::string>();
    return nullptr;
}

nlohmann::json EntitySerializer::toJson(const IEntity* entity) const
{
    auto jsonObject = nlohmann::json::object();
    jsonObject["type"] = entity->type();
    jsonObject["id"] = entity->id();
    auto jsonProperties = nlohmann::json::array();
    for (const auto& propertyName : entity->listPropertyNames())
    {
        const auto& property = entity->property(propertyName);
        auto jsonProperty = nlohmann::json::object();
        jsonProperty["name"] = property.name();
        jsonProperty["displayName"] = property.displayName();
        //jsonProperty["data"] = property.data();
        jsonProperties.push_back(jsonProperty);
    }
    jsonObject["properties"] = jsonProperties;
    return jsonObject;
}
