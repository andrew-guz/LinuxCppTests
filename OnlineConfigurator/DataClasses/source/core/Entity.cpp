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

std::vector<std::string> Entity::listPropertyNames() const
{
    std::vector<std::string> result;
    std::transform(_properties.begin(), _properties.end(), std::back_inserter(result), [](const auto& property){
        return property.name();
    });
    return result;
}

bool Entity::hasProperty(const std::string& name) const
{
    return std::find_if(_properties.begin(), _properties.end(), [name](const auto& property){ return property.name() == name; }) != _properties.end();
}

Property& Entity::property(const std::string& name)
{
    auto iter = std::find_if(_properties.begin(), _properties.end(), [name](const auto& property){ return property.name() == name; });
    assert(iter != _properties.end());
    return *iter;
}

const Property& Entity::property(const std::string& name) const
{
    auto iter = std::find_if(_properties.begin(), _properties.end(), [name](const auto& property){ return property.name() == name; });
    assert(iter != _properties.end());
    return *iter;
}

const Variant& Entity::propertyValue(const std::string& name) const
{
    auto iter = std::find_if(_properties.begin(), _properties.end(), [name](const auto& property){ return property.name() == name; });
    assert(iter != _properties.end());
    return iter->data();
}

std::vector<std::string> Entity::listSubEntityNames() const
{
    std::vector<std::string> result;
    std::transform(_subEntities.begin(), _subEntities.end(), std::back_inserter(result), [](const auto& pair){
        return pair.first;
    });
    return result;
}

bool Entity::hasSubEntity(const std::string& name) const
{
    return _subEntities.find(name) != _subEntities.end();
}

IEntity* Entity::subEntity(const std::string& name)
{
    auto iter = _subEntities.find(name);
    assert(iter != _subEntities.end());
    return iter->second;
}

const IEntity* Entity::subEntity(const std::string& name) const
{
    auto iter = _subEntities.find(name);
    assert(iter != _subEntities.end());
    return iter->second;
}

void Entity::addProperty(const std::string& name, const std::string& displayName, const Variant& data, const PropertyAdditions::PropertyEditorInfo& editorInfo)
{
    _properties.emplace_back(name, displayName, data, editorInfo);
}
