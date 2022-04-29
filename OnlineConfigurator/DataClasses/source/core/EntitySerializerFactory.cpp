#include "EntitySerializerFactory.h"

#include <cassert>

#include "EntitySerializer.h"

EntitySerializerFactory::EntitySerializerFactory()
{
    //register here not standart serializers
}

std::shared_ptr<ISerializer> EntitySerializerFactory::getSerializer(const std::string& type)
{
    auto iter = _serializers.find(type);
    //do not blame for unknown type - return EntitySerializer - that will help to register only specific entities
    if (iter != _serializers.end())
        return iter->second;
    return std::make_shared<EntitySerializer>();
}

void EntitySerializerFactory::registerSerializer(const std::string& type, std::shared_ptr<ISerializer> serializer)
{
    auto iter = _serializers.find(type);
    assert(iter == _serializers.end());
    _serializers.emplace(type, serializer);
}
