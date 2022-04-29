#ifndef _PROPERTY_H_
#define _PROPERTY_H_

#include <string>

#include "Variant.h"
#include "PropertyEditorInfo.h"

class Property final
{
public:
    Property(const std::string& name, const std::string& displayName, const Variant& data = {}, const PropertyAdditions::PropertyEditorInfo& editorInfo = {});

    Property(const Property& property);

    ~Property() = default;

    Property& operator=(const Property& other);

    Property& operator=(const Variant& data);

    bool operator==(const Property& other) const;

    bool operator!=(const Property& other) const;

    const std::string& name() const;

    const std::string& displayName() const;

    const Variant& data() const;

    const PropertyAdditions::PropertyEditorInfo& editorInfo() const;

private:
    std::string                             _name;
    std::string                             _displayName;
    Variant                                 _data;
    PropertyAdditions::PropertyEditorInfo   _editorInfo;
};

#endif //_PROPERTY_H_
