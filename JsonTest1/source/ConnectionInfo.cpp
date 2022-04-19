#include <tuple>

#include "ConnectionInfo.h"

bool ConnectionInfo::operator==(const ConnectionInfo& other) const
{
    return std::tie(_mainAddress, _additionalAddress, _password) ==
           std::tie(other._mainAddress, other._additionalAddress, other._password);
}

bool ConnectionInfo::operator!=(const ConnectionInfo& other) const
{
    return std::tie(_mainAddress, _additionalAddress, _password) !=
           std::tie(other._mainAddress, other._additionalAddress, other._password);
}