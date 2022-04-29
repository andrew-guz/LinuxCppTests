#include "EntitySerializerFactory.h"

#include <cassert>

#include "EntitySerializer.h"

EntitySerializerFactory::EntitySerializerFactory()
{
    registerSerializer("connectionInformation", std::make_shared<EntitySerializer>());
    registerSerializer("project",               std::make_shared<EntitySerializer>());
    registerSerializer("voltageLimits",         std::make_shared<EntitySerializer>());
    registerSerializer("errorProcessing",       std::make_shared<EntitySerializer>());
}

std::shared_ptr<ISerializer> EntitySerializerFactory::getSerializer(const std::string& type)
{
    auto iter = _serializers.find(type);
    assert(iter != _serializers.end());
    return iter->second;
}

void EntitySerializerFactory::registerSerializer(const std::string& type, std::shared_ptr<ISerializer> serializer)
{
    auto iter = _serializers.find(type);
    assert(iter == _serializers.end());
    _serializers.emplace(type, serializer);
}
