#ifndef _ENTITYBUILDHELPER_H_
#define _ENTITYBUILDHELPER_H_

#include "EntityFactory.h"
#include "EntitySerializerFactory.h"
#include "EntitySerializer.h"

#define CTOR(CLASS) \
    if (!EntitySerializerFactory::instance()->isRegistered(type())) \
        EntitySerializerFactory::instance()->registerSerializer(type(), std::make_shared<EntitySerializer>()); \
    if (!EntityFactory::instance()->isRegistered(type())) \
        EntityFactory::instance()->registerCreationFunction(type(), [](const Uuid& id) \
        { \
            return new CLASS(id); \
        }); \

#endif //_ENTITYBUILDHELPER_H_
