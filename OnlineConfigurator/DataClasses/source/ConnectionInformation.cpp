#include "ConnectionInformation.h"

#include "EntityBuildHelper.h"

ConnectionInformation::ConnectionInformation(const Uuid& id) :
    Entity("connectionInformation", id)
{
    CTOR(ConnectionInformation);
    
    //fill properties
    addProperty("mainAddress", "Main address", std::string());
    addProperty("additionalAddress", "Additional address", std::string());
    addProperty("password", "Password", std::string());
    
    //fill subEntities
}
