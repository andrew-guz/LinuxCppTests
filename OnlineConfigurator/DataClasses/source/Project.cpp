#include "Project.h"

#include "ConnectionInformation.h"

Project::Project(bool withSubEntities, const Uuid& id) :
    Entity("project", withSubEntities, id)
{
    //fill properties
    addProperty("name", u8"Имя контроллера", std::string());
    
    //fill subEntities
    addSubEntity<ConnectionInformation>("connectionInformation");
}
