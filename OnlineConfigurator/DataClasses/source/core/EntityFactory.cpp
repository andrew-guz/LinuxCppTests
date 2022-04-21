#include <cassert>

#include "EntityFactory.h"

void EntityFactory::registercreationFunction(const std::string& type, EntityCreationFunction function)
{
    auto iter = _creators.find(type);
    assert(iter == _creators.end());
    _creators.insert(std::make_pair(type, function));
}

IEntity* EntityFactory::createEntity(const std::string& type, const std::string& id) const
{
    auto iter = _creators.find(type);
    assert(iter != _creators.end());
    return (iter->second)(id);
}
