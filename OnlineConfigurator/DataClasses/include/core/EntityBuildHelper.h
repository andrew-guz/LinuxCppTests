#ifndef _ENTITYBUILDHELPER_H_
#define _ENTITYBUILDHELPER_H_

#include "EntitySerializerFactory.h"
#include "EntitySerializer.h"
#include "EntityFactory.h"

#define CTOR(CLASS) \
    EntitySerializerFactory::instance()->registerSerializer(type(), std::make_shared<EntitySerializer>()); \
    EntityFactory::instance()->registerCreationFunction(type(), [](const Uuid& id) \
    { \
        return new CLASS(id); \
    }); \

#endif //_ENTITYBUILDHELPER_H_
