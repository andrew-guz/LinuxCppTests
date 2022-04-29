#include "Entity.h"

#include <cassert>
#include <algorithm>

#include "EntityPool.h"

Entity::Entity(const std::string& type, bool withSubEntities, const Uuid& id) :
    _type(type),
    _withSubEntities(withSubEntities),
    _id(id)
{
    EntityPool::instance()->add(this);
}

Entity::~Entity()
{
    for (auto& pair : _subEntities)
        delete pair.second;
    EntityPool::instance()->remove(this);
}

const std::string& Entity::type() const
{
    return _type;
}

const Uuid& Entity::id() const
{
    return _id;
}

template<typename T>
bool contains(const std::map<std::string, T>& map, const std::string& name)
{
    auto iter = map.find(name);
    return iter != map.end();
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

bool Entity::hasProperty(const std::string& name) const
{
    return contains(_properties, name);
}

Property& Entity::property(const std::string& name)
{
    return search(_properties, name);
}

const Property& Entity::property(const std::string& name) const
{
    return search(_properties, name);
}

const Variant& Entity::propertyValue(const std::string& name) const
{
    return search(_properties, name).data();
}

std::vector<std::string> Entity::listSubEntityNames() const
{
    return list(_subEntities);
}

bool Entity::hasSubEntity(const std::string& name) const
{
    return contains(_subEntities, name);
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
    _properties.emplace(name, Property(name, displayName, data));
}
