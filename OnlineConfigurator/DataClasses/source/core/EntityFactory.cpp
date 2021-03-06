#include "EntityFactory.h"

#include <cassert>

#include "ConnectionInformation.h"
#include "Project.h"
#include "VoltageLimits.h"
#include "ErrorProcessing.h"

EntityFactory::EntityFactory()
{
    registerCreationFunction("connectionInformation",   [](bool withSubEntities, const Uuid& id) { return new ConnectionInformation(withSubEntities, id); });
    registerCreationFunction("project",                 [](bool withSubEntities, const Uuid& id) { return new Project(withSubEntities, id); });
    registerCreationFunction("voltageLimits",           [](bool withSubEntities, const Uuid& id) { return new VoltageLimits(withSubEntities, id); });
    registerCreationFunction("errorProcessing",         [](bool withSubEntities, const Uuid& id) { return new ErrorProcessing(withSubEntities, id); });
}

Entity* EntityFactory::createEntity(const std::string& type, bool withSubEntities, const Uuid& id) const
{
    auto iter = _creators.find(type);
    assert(iter != _creators.end());
    if (iter != _creators.end())
        return (iter->second)(withSubEntities, id);
    return nullptr;
}

void EntityFactory::registerCreationFunction(const std::string& type, EntityCreationFunction function)
{
    auto iter = _creators.find(type);
    assert(iter == _creators.end());
    _creators.emplace(type, function);
}
