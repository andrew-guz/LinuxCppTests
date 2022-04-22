#ifndef _IFACTORY_H_
#define _IFACTORY_H_

#include <string>

class ITypeFactory
{
public:
    virtual ~ITypeFactory() = default;

public:
    virtual bool isRegistered(const std::string& type) const = 0;
};

#endif //_IFACTORY_H_