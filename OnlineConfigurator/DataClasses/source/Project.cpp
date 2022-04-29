#include "Project.h"

#include "ConnectionInformation.h"
#include "VoltageLimits.h"
#include "ErrorProcessing.h"

Project::Project(bool withSubEntities, const Uuid& id) :
    Entity("project", withSubEntities, id)
{
    //fill properties
    addProperty("name", u8"Имя контроллера", std::string());
    
    //fill subEntities
    addSubEntity<ConnectionInformation>("connectionInformation");
    addSubEntity<VoltageLimits>("voltageLimits");
    addSubEntity<ErrorProcessing>("errorProcessing");
}
