#include <cassert>
#include <algorithm>

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

template<typename T>
std::vector<std::string> list(const std::map<std::string, T>& map)
{
    std::vector<std::string> result;
    std::transform(map.begin(), map.end(), std::back_inserter(result), [](const std::pair<std::string, T>& pair){
        return pair.first;
    });
    return result;
}

std::vector<std::string> Entity::listPropertyNames() const
{
    return list(_properties);
}

Property& Entity::property(const std::string& name)
{
    return search(_properties, name);
}

const Property& Entity::property(const std::string& name) const
{
    return search(_properties, name);
}

std::vector<std::string> Entity::listSubEntityNames() const
{
    return list(_subEntities);
}

IEntity* Entity::subEntity(const std::string& name)
{
    return search(_subEntities, name);
}

const IEntity* Entity::subEntity(const std::string& name) const
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
