#ifndef _ISERIALIZER_H_
#define _ISERIALIZER_H_

#include <string>

#include "IEntity.h"

class ISerializer
{
public:
    virtual ~ISerializer() = default;

    virtual std::string toString(const IEntity* entity) const = 0;

    virtual IEntity* toEntity(const std::string& str) const = 0;
};

#endif //_ISERIALIZER_H_
