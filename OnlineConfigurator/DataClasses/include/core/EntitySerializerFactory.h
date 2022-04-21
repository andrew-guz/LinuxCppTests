#ifndef _ENTITYSERIALIZERFACTORY_H_
#define _ENTITYSERIALIZERFACTORY_H_

#include <memory>

#include "Singleton.h"
#include "ISerializer.h"

class EntitySerializerFactory final : public Singleton<EntitySerializerFactory>
{
public:
    std::shared_ptr<ISerializer> createSerializer();
};

#endif //_ENTITYSERIALIZERFACTORY_H_
