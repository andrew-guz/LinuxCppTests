#ifndef _ENTITYSERIALIZER_H_
#define _ENTITYSERIALIZER_H_

#include <nlohmann/json.hpp>

#include "ISerializer.h"

class EntitySerializer : public ISerializer
{
public:
    virtual ~EntitySerializer() = default;

    virtual std::string toString(const IEntity* entity) const override;

    virtual IEntity* toEntity(const std::string& str) const override;

protected:
    virtual nlohmann::json toJson(const IEntity* entity) const;

private:
    friend class EntityFactory;
};

#endif //_ENTITYSERIALIZER_H_