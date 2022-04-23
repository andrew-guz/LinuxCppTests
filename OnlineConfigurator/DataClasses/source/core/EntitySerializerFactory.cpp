#include "EntitySerializerFactory.h"

#include <cassert>

bool EntitySerializerFactory::isRegistered(const std::string& type) const
{
    auto iter = _serializers.find(type);
    return iter != _serializers.end();
}

void EntitySerializerFactory::registerSerializer(const std::string& type, std::shared_ptr<ISerializer> serializer)
{
    auto iter = _serializers.find(type);
    assert(iter == _serializers.end());
    _serializers.emplace(type, serializer);
}

std::shared_ptr<ISerializer> EntitySerializerFactory::getSerializer(const std::string& type)
{
    auto iter = _serializers.find(type);
    assert(iter != _serializers.end());
    return iter->second;
}
