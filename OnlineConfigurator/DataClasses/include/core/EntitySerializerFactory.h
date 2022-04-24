#ifndef _ENTITYSERIALIZERFACTORY_H_
#define _ENTITYSERIALIZERFACTORY_H_

#include <memory>
#include <map>

#include "Singleton.h"
#include "ISerializer.h"

class EntitySerializerFactory final : public Singleton<EntitySerializerFactory>
{
public:
    EntitySerializerFactory();

    std::shared_ptr<ISerializer> getSerializer(const std::string& type);

protected:
    void registerSerializer(const std::string& type, std::shared_ptr<ISerializer> serializer);

private:
    std::map<std::string, std::shared_ptr<ISerializer>> _serializers;
};

#endif //_ENTITYSERIALIZERFACTORY_H_
