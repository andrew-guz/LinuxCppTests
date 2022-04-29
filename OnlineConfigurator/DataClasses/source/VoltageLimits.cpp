#include "VoltageLimits.h"

VoltageLimits::VoltageLimits(bool withSubEntities, const Uuid& id) :
    Entity("voltageLimits", withSubEntities, id)
{
    //fill properties
    addProperty("voltage220low", "", 180);
    addProperty("voltage220high", "", 260);
    addProperty("voltage24low", "", 21);
    addProperty("voltage23high", "", 26);    
    
    //fill subEntities    
}
