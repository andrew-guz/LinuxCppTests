#ifndef _ISERIALIZER_H_
#define _ISERIALIZER_H_

#include "IEntity.h"

#include <string>

class ISerializer
{
public:
    virtual ~ISerializer() = default;

    virtual std::string toString(const IEntity* entity) = 0;

    virtual IEntity* toEntity(const std::string& str) = 0;
};

#endif //_ISERIALIZER_H_
