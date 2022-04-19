#include "Variant.h"

#include <tuple>

Variant::Variant(bool value) :
    _isEmpty(false),
    _data(value)
{}

Variant::Variant(int value) :
    _isEmpty(false),
    _data(value)
{}

Variant::Variant(float value) :
    _isEmpty(false),
    _data(value)
{}

Variant::Variant(const std::string& value) :
    _isEmpty(false),
    _data(value)
{}

Variant::Variant(const Variant& other) :
    _isEmpty(other._isEmpty),
    _data(other._data)
{}

Variant& Variant::operator=(bool value)
{
    _isEmpty = false;
    _data = value;
    return *this;
}

Variant& Variant::operator=(int value)
{
    _isEmpty = false;
    _data = value;
    return *this;
}

Variant& Variant::operator=(float value)
{
    _isEmpty = false;
    _data = value;
    return *this;
}

Variant& Variant::operator=(const std::string& value)
{
    _isEmpty = false;
    _data = value;
    return *this;
}

bool Variant::operator==(const Variant& other) const
{
    return std::tie(_isEmpty, _data) == std::tie(other._isEmpty, other._data);
}

bool Variant::operator!=(const Variant& other) const
{
    return std::tie(_isEmpty, _data) != std::tie(other._isEmpty, other._data);
}

bool Variant::isEmpty() const
{
    return _isEmpty;
}

bool Variant::toBool() const
{
    return _isEmpty ? false : std::get<bool>(_data);
}

int Variant::toInt() const
{
    return _isEmpty ? 0 : std::get<int>(_data);
}

float Variant::toFloat() const
{
    return _isEmpty ? 0.0f : std::get<float>(_data);
}

std::string Variant::toString() const
{
    return _isEmpty ? std::string{} : std::get<std::string>(_data);
}
