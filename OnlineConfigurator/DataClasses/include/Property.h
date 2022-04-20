#ifndef _PROPERTY_H_
#define _PROPERTY_H_

#include <string>

#include "Variant.h"

class Property final
{
public:
    Property(const std::string& name, const std::string& displayName, const Variant& data = {});

    Property(const Property& property);

    ~Property() = default;

    Property& operator=(const Property& other);

    bool operator==(const Property& other) const;

    bool operator!=(const Property& other) const;

public:
    const std::string& name() const;

    const std::string& displayName() const;

    const Variant& data() const;

    void setData(const Variant& data);

private:
    std::string _name;
    std::string _displayName;
    Variant     _data;
};

#endif //_PROPERTY_H_
