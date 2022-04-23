#include "Project.h"

#include "EntityBuildHelper.h"
#include "ConnectionInformation.h"

Project::Project(const Uuid& id) :
    Entity("project", id)
{
    CTOR(Project);
    
    //fill properties
    addProperty("name", "Name", std::string());
    
    //fill subEntities
    addSubEntity("connectionInformation", new ConnectionInformation());
}
