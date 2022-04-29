#ifndef _ERRORPROCESSING_H_
#define _ERRORPROCESSING_H_

#include "Entity.h"

class ErrorProcessing final : public Entity
{
public:
    ErrorProcessing(bool withSubEntities = true, const Uuid& id = {});

    virtual ~ErrorProcessing() = default;
};

#endif //_ERRORPROCESSING_H_
