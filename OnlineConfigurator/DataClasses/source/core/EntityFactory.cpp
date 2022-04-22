#include "EntityFactory.h"

#include <cassert>

bool EntityFactory::isRegistered(const std::string& type) const
{
    auto iter = _creators.find(type);
    return iter != _creators.end();
}

void EntityFactory::registerCreationFunction(const std::string& type, EntityCreationFunction function)
{
    auto iter = _creators.find(type);
    assert(iter == _creators.end());
    _creators.emplace(type, function);
}

Entity* EntityFactory::createEntity(const std::string& type, const Uuid& id) const
{
    auto iter = _creators.find(type);
    assert(iter != _creators.end());
    return (iter->second)(id);
}
