#ifndef _ENTITYFACTORY_H_
#define _ENTITYFACTORY_H_

#include <functional>
#include <map>

#include "Singleton.h"
#include "Entity.h"

typedef std::function<Entity*(const std::string&)> EntityCreationFunction;

class EntityFactory final : public Singleton<EntityFactory>
{
public:
    virtual ~EntityFactory() = default;

    void registercreationFunction(const std::string& type, EntityCreationFunction function);

    Entity* createEntity(const std::string& type, const std::string& id) const;

private:
    std::map<std::string, EntityCreationFunction> _creators;
};

#endif //_ENTITYFACTORY_H_
