#include <cassert>

#include "Entity.h"

Entity::Entity()
{
    uuid_generate_random(_id);
}

Entity::Entity(const uuid_t& id)
{
    uuid_copy(_id, id);
}

Entity::~Entity()
{
    for (auto& pair : _subEntities)
        delete pair.second;
}

const uuid_t& Entity::id() const
{
    return _id;
}

template<typename T>
T& search(std::map<std::string, T>& map, const std::string& name)
{
    auto iter = map.find(name);
    assert(iter != map.end());
    return iter->second;
}

template<typename T>
const T& search(const std::map<std::string, T>& map, const std::string& name)
{
    auto iter = map.find(name);
    assert(iter != map.end());
    return iter->second;
}


Property& Entity::operator[](const std::string& name)
{
    return search(_properties, name);
}

const Property& Entity::operator[](const std::string& name) const
{
    return search(_properties, name);
}

IEntity* Entity::getSubEntity(const std::string& name)
{
    return search(_subEntities, name);
}

const IEntity* Entity::getSubEntity(const std::string& name) const
{
    return search(_subEntities, name);
}

void Entity::addProperty(const std::string& name, const std::string& displayName, const Variant& data)
{
    _properties.insert(std::make_pair(name, Property(name, displayName, data)));
}

void Entity::addSubEntity(const std::string& name, IEntity* entity)
{
    _subEntities.insert(std::make_pair(name, entity));
}
