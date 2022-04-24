#ifndef _ENTITYFACTORY_H_
#define _ENTITYFACTORY_H_

#include <functional>
#include <map>

#include "Singleton.h"
#include "Entity.h"

typedef std::function<Entity*(bool, const Uuid&)> EntityCreationFunction;

class EntityFactory final : public Singleton<EntityFactory>
{
public:
    EntityFactory();

    Entity* createEntity(const std::string& type, bool withSubEntities, const Uuid& id) const;

protected:
    void registerCreationFunction(const std::string& type, EntityCreationFunction function);

private:
    std::map<std::string, EntityCreationFunction> _creators;
};

#endif //_ENTITYFACTORY_H_
