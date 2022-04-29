#include "Property.h"

#include <cassert>
#include <tuple>

Property::Property(const std::string& name, const std::string& displayName, const Variant& data, const PropertyAdditions::PropertyEditorInfo& editorInfo) :
    _name(name),
    _displayName(displayName),
    _data(data),
    _editorInfo(editorInfo)
{
    assert(name.size());
    assert(displayName.size());
}

Property::Property(const Property& property) :
    _name(property._name),
    _displayName(property._displayName),
    _data(property._data),
    _editorInfo(property._editorInfo)
{
    
}

Property& Property::operator=(const Property& other)
{
    _name = other._name;
    _displayName = other._displayName;
    _data = other._data;
    _editorInfo = other._editorInfo;
    return *this;
}

Property& Property::operator=(const Variant& data)
{
    _data = data;
    return *this;
}

bool Property::operator==(const Property& other) const
{
    return std::tie(_name, _data) == std::tie(other._name, other._data);
}

bool Property::operator!=(const Property& other) const
{
    return std::tie(_name, _data) != std::tie(other._name, other._data);
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

const PropertyAdditions::PropertyEditorInfo& Property::editorInfo() const
{
    return _editorInfo;
}
