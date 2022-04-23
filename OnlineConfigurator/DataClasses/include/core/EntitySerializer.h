#ifndef _ENTITYSERIALIZER_H_
#define _ENTITYSERIALIZER_H_

#include "ISerializer.h"

class EntitySerializer : public ISerializer
{
public:
    virtual ~EntitySerializer() = default;

    virtual nlohmann::json toJson(const IEntity* entity, bool recursive) const override;

    virtual IEntity* toEntity(const nlohmann::json& jsonObject) const override;
};

#endif //_ENTITYSERIALIZER_H_