#include "ErrorProcessing.h"

ErrorProcessing::ErrorProcessing(bool withSubEntities, const Uuid& id) :
    Entity("errorProcessing", withSubEntities, id)
{
    //fill properties
    addProperty("triesCount",           u8"Число попыток восстановления работоспособности",             3,      { PropertyAdditions::EditorType::Integer, std::make_shared<PropertyAdditions::IntegerLimits>(0, 10) });
    addProperty("channelPause",         u8"Паузы при восстановлении работоспособности каналов (сек)",   5,      { PropertyAdditions::EditorType::Integer, std::make_shared<PropertyAdditions::IntegerLimits>(0, 10) });
    addProperty("restorePause",         u8"Паузы при восстановлении режима (мин)",                      10,     { PropertyAdditions::EditorType::Integer, std::make_shared<PropertyAdditions::IntegerLimits>(0, 100) });
    addProperty("currentTimeout",       u8"Задержка замера токов (сек)",                                2,      { PropertyAdditions::EditorType::Integer, std::make_shared<PropertyAdditions::IntegerLimits>(0, 10) });
    addProperty("contactFixTimeout",    u8"Время подавления дребезга контактов кнопок (мс)",            100,    { PropertyAdditions::EditorType::Integer, std::make_shared<PropertyAdditions::IntegerLimits>(0, 1000) });
    
    //fill subEntities    
}
