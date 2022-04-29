#ifndef _ISERIALIZER_H_
#define _ISERIALIZER_H_

#include <memory>

#include <nlohmann/json.hpp>

#include "IEntity.h"

class ISerializer
{
public:
    virtual ~ISerializer() = default;

    virtual nlohmann::json toJson(const IEntity* entity, bool withSubEntities) const = 0;

    virtual IEntity* toEntity(const nlohmann::json& jsonObject) const = 0;

    std::shared_ptr<IEntity> toEntitySharedPtr(const nlohmann::json& jsonObject)
    {
        return std::shared_ptr<IEntity>(toEntity(jsonObject));
    }
};

#endif //_ISERIALIZER_H_
