#include "ConnectionInformation.h"

ConnectionInformation::ConnectionInformation(bool withSubEntities, const Uuid& id) :
    Entity("connectionInformation", withSubEntities, id)
{   
    //fill properties
    addProperty("mainAddress",          u8"Основной адрес",         std::string("192.168.3."),  { PropertyAdditions::EditorType::LineEdit, nullptr });
    addProperty("additionalAddress",    u8"Дополнительный адрес",   std::string(),              { PropertyAdditions::EditorType::LineEdit, nullptr });
    addProperty("password",             u8"Пароль",                 std::string(),              { PropertyAdditions::EditorType::PasswordLineEdit, nullptr });
    
    //fill subEntities
}
