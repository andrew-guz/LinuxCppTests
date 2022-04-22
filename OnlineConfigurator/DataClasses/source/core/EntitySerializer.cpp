#include "EntitySerializer.h"

#include "UuidSerializer.h"
#include "VariantSerializer.h"
#include "EntitySerializerFactory.h"
#include "EntityFactory.h"

nlohmann::json EntitySerializer::toJson(const IEntity* entity, bool withSubEntities) const
{
    auto jsonObject = nlohmann::json::object();
    jsonObject["type"] = entity->type();
    jsonObject["id"] = UuidSerializer::toJson(entity->id());
    auto jsonProperties = nlohmann::json::array();
    for (const auto& propertyName : entity->listPropertyNames())
    {
        const auto& property = entity->property(propertyName);
        auto jsonProperty = nlohmann::json::object();
        jsonProperty["name"] = property.name();
        jsonProperty["displayName"] = property.displayName();
        jsonProperty["data"] = VariantSerializer::toJson(property.data());
        jsonProperties.push_back(jsonProperty);
    }
    jsonObject["properties"] = jsonProperties;
    auto jsonSubEntities = nlohmann::json::array();
    if (withSubEntities)
    {
        for (const auto& subEntityName : entity->listSubEntityNames())
        {
            const auto& subEntity = entity->subEntity(subEntityName);
            auto jsonSubEntity = nlohmann::json::object();
            jsonSubEntity["type"] = subEntity->type();
            jsonSubEntity["name"] = subEntityName;
            auto serializer = EntitySerializerFactory::instance()->createSerializer(subEntity->type());
            jsonSubEntity["entity"] = serializer->toJson(subEntity);
            jsonSubEntities.push_back(jsonSubEntity);
        }
    }
    jsonObject["subEntities"] = jsonSubEntities;
    return jsonObject;
}

IEntity* EntitySerializer::toEntity(const nlohmann::json& jsonObject) const
{
    auto type = jsonObject["type"].get<std::string>();
    auto id = UuidSerializer::fromJson(jsonObject["id"]);
    auto entity = EntityFactory::instance()->createEntity(type, id);
    for (const auto& jsonProperty : jsonObject["properties"])
    {
        auto name = jsonProperty.value<std::string>("name", "");
        auto displayName = jsonProperty.value<std::string>("displayName", "");
        auto data = VariantSerializer::fromJson(jsonProperty["data"]);
        entity->addProperty(name, displayName, data);
    }
    for (const auto& jsonSubEntity : jsonObject["subEntities"])
    {
        auto type = jsonSubEntity["type"].get<std::string>();
        auto name = jsonSubEntity["name"].get<std::string>();
        auto jsonData = jsonSubEntity["data"];
        auto serializer = EntitySerializerFactory::instance()->createSerializer(type);
        entity->addSubEntity(name, serializer->toEntity(jsonData));
    }
    return entity;
}
