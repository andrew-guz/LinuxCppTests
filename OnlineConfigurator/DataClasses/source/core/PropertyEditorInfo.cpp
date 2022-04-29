#include "PropertyEditorInfo.h"

using namespace PropertyAdditions;

AdditionalInformation::AdditionalInformation(AdditionalInformationType type) :
    _type(type)
{

}

AdditionalInformationType AdditionalInformation::type() const
{
    return _type;
}

IntegerLimits::IntegerLimits(int min, int max) :
    AdditionalInformation(AdditionalInformationType::IntLimits),
    _min(min),
    _max(max)
{
    
}
