#include <cassert>
#include <tuple>

#include "Property.h"

Property::Property(const std::string& name, const std::string& displayName, const Variant& data) :
    _name(name),
    _displayName(displayName),
    _data(data)
{
    assert(name.size());
    assert(displayName.size());
}

Property::Property(const Property& property) :
    _name(property._name),
    _displayName(property._displayName),
    _data(property._data)
{
    
}

Property& Property::operator=(const Property& other)
{
    _name = other._name;
    _displayName = other._displayName;
    _data = other._data;
    return *this;
}

bool Property::operator==(const Property& other) const
{
    return std::tie(_name, _displayName, _data) == std::tie(other._name, other._displayName, other._data);
}

bool Property::operator!=(const Property& other) const
{
    return std::tie(_name, _displayName, _data) != std::tie(other._name, other._displayName, other._data);
}

const std::string& Property::name() const
{
    return _name;
}

const std::string& Property::displayName() const
{
    return _displayName;
}

const Variant& Property::data() const
{
    return _data;
}

void Property::setData(const Variant& data)
{
    _data = data;
}
