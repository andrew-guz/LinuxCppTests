#include "EntityPool.h"

#include <cassert>

void EntityPool::add(IEntity* entity)
{
    auto iter = _entities.find(entity->id());
    assert(iter == _entities.end());
    _entities.emplace(entity->id(), entity);
}

void EntityPool::remove(IEntity* entity)
{
    auto iter = _entities.find(entity->id());
    assert(iter != _entities.end());
    _entities.erase(iter);
}

IEntity* EntityPool::find(const Uuid& id)
{
    auto iter = _entities.find(id);
    if (iter != _entities.end())
        return iter->second;
    return nullptr;
}

const IEntity* EntityPool::find(const Uuid& id) const
{
    auto iter = _entities.find(id);
    if (iter != _entities.end())
        return iter->second;
    return nullptr;
}
