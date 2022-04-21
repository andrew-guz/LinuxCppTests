#ifndef _IENTITY_H_
#define _IENTITY_H_

#include <vector>
#include <uuid/uuid.h>

#include "Property.h"

class IEntity
{
public:
    virtual ~IEntity() = default;

public:
    virtual const std::string& type() const = 0;

    virtual const uuid_t& id() const = 0;

    virtual std::vector<std::string> listPropertyNames() const = 0; 

    virtual Property& property(const std::string& name) = 0;

    virtual const Property& property(const std::string& name) const = 0;

    virtual std::vector<std::string> listSubEntityNames() const = 0;

    virtual IEntity* subEntity(const std::string& name) = 0;

    virtual const IEntity* subEntity(const std::string& name) const = 0;
};

#endif //_IENTITY_H_
