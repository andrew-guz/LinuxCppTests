#ifndef _VARIANTSERIALIZER_H
#define _VARIANTSERIALIZER_H

#include <nlohmann/json.hpp>

#include "Variant.h"

class VariantSerializer final
{
public:
    virtual ~VariantSerializer() = default;

    static nlohmann::json toJson(const Variant& data);

    static Variant fromJson(const nlohmann::json& json);
};

#endif //_VARIANTSERIALIZER_H
