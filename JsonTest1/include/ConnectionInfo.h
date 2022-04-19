#ifndef _CONNECTIONINFO_H_
#define _CONNECTIONINFO_H_

#include <string>

class ConnectionInfo
{
public:
    std::string _mainAddress;
    std::string _additionalAddress;
    std::string _password;

    bool operator==(const ConnectionInfo& other) const;

    bool operator!=(const ConnectionInfo& other) const;
};

#endif //_CONNECTIONINFO_H_