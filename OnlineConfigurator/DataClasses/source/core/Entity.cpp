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

const uuid_t& Entity::id() const
{
    return _id;
}

 Property& Entity::operator[](const std::string& name)
 {
    auto iter = _properties.find(name);
    assert(iter != _properties.end());
    return iter->second;
 }

const Property& Entity::operator[](const std::string& name) const
{
    auto iter = _properties.find(name);
    assert(iter != _properties.end());
    return iter->second;
}

void Entity::addProperty(const std::string& name, const std::string& displayName, const Variant& data)
{
    _properties.insert(std::make_pair(name, Property(name, displayName, data)));
}
