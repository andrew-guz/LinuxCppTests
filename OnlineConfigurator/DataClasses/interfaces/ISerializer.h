#ifndef _ISERIALIZER_H_
#define _ISERIALIZER_H_

#include <nlohmann/json.hpp>

#include "IEntity.h"

class ISerializer
{
public:
    virtual ~ISerializer() = default;

    virtual nlohmann::json toJson(const IEntity* entity) const = 0;

    virtual IEntity* toEntity(const nlohmann::json& jsonObject) const = 0;
};

#endif //_ISERIALIZER_H_
