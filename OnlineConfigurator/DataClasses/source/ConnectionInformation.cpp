#include "ConnectionInformation.h"

ConnectionInformation::ConnectionInformation(bool withSubEntities, const Uuid& id) :
    Entity("connectionInformation", withSubEntities, id)
{   
    //fill properties
    addProperty("mainAddress", u8"Основной адрес", std::string());
    addProperty("additionalAddress", u8"Дополнительный адрес", std::string());
    addProperty("password", u8"Пароль", std::string());
    
    //fill subEntities

    //some presetup values
    property("mainAddress") = std::string("192.168.3.");
}
