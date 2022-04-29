#include "ErrorProcessing.h"

ErrorProcessing::ErrorProcessing(bool withSubEntities, const Uuid& id) :
    Entity("errorProcessing", withSubEntities, id)
{
    //fill properties
    addProperty("triesCount", u8"Число попыток восстановления работоспособности", 3);
    addProperty("triesCount", u8"Паузы при восстановлении работоспособности каналов (сек)", 5);
    addProperty("triesCount", u8"Паузы при восстановлении режима (мин)", 10);
    addProperty("triesCount", u8"Задержка замера токов (сек)", 2);
    addProperty("triesCount", u8"Время подавления дребезга контактов кнопок (мс)", 100);
    
    //fill subEntities    
}
