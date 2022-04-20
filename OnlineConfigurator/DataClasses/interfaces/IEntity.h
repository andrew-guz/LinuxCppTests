#ifndef _IENTITY_H_
#define _IENTITY_H_

#include <uuid/uuid.h>

#include "Property.h"

class IEntity
{
public:
    virtual ~IEntity() = default;

public:
    virtual const uuid_t& id() const = 0;

    virtual Property& operator[](const std::string& name) = 0;

    virtual const Property& operator[](const std::string& name) const = 0;
};

#endif //_IENTITY_H_
