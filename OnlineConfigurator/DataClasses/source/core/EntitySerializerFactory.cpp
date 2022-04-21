#include "EntitySerializerFactory.h"

#include "EntitySerializer.h"

std::shared_ptr<ISerializer> EntitySerializerFactory::createSerializer()
{
    return std::make_shared<EntitySerializer>();
}
