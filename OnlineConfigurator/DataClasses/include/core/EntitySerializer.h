#ifndef _ENTITYSERIALIZER_H_
#define _ENTITYSERIALIZER_H_

#include "ISerializer.h"

class EntitySerializer : public ISerializer
{
public:
    virtual ~EntitySerializer() = default;

    virtual std::string toString(const IEntity* entity) override;

    virtual IEntity* toEntity(const std::string& str) override;
};

#endif //_ENTITYSERIALIZER_H_