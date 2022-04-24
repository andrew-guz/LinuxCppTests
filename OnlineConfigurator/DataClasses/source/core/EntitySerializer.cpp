#include "EntitySerializer.h"

#include "VariantSerializer.h"
#include "EntitySerializerFactory.h"
#include "EntityFactory.h"

nlohmann::json EntitySerializer::toJson(const IEntity* entity, bool withSubEntities) const
{
    auto jsonObject = nlohmann::json::object();
    jsonObject["withSubEntities"] = withSubEntities;
    jsonObject["type"] = entity->type();
    jsonObject["id"] = entity->id().data();
    auto jsonProperties = nlohmann::json::array();
    for (const auto& propertyName : entity->listPropertyNames())
    {
        const auto& property = entity->property(propertyName);
        auto jsonProperty = nlohmann::json::object();
        jsonProperty["name"] = property.name();
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
            jsonSubEntity["name"] = subEntityName;
            auto serializer = EntitySerializerFactory::instance()->getSerializer(subEntity->type());
            jsonSubEntity["entity"] = serializer->toJson(subEntity, withSubEntities);
            jsonSubEntities.push_back(jsonSubEntity);
        }
    }
    jsonObject["subEntities"] = jsonSubEntities;
    return jsonObject;
}

IEntity* EntitySerializer::toEntity(const nlohmann::json& jsonObject) const
{
    bool withSubEntities = jsonObject["withSubEntities"].get<bool>();
    auto type = jsonObject["type"].get<std::string>();
    auto id = Uuid(jsonObject["id"].get<std::string>());
    auto entity = EntityFactory::instance()->createEntity(type, false, id);
    for (const auto& jsonProperty : jsonObject["properties"])
    {
        auto name = jsonProperty.value<std::string>("name", "");        
        auto data = VariantSerializer::fromJson(jsonProperty["data"]);
        entity->property(name) = data;
    }
    if (withSubEntities)
    {
        for (const auto& jsonSubEntity : jsonObject["subEntities"])
        {
            auto name = jsonSubEntity["name"].get<std::string>();
            auto jsonData = jsonSubEntity["data"];            
            auto type = jsonData["type"].get<std::string>();
            auto serializer = EntitySerializerFactory::instance()->getSerializer(type);            
            auto subEntity = serializer->toEntity(jsonData);
            entity->_subEntities.emplace(name, subEntity);
        }
    }
    return entity;
}
