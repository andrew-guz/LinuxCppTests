#include <iostream>

#include "ConnectionInfo.h"
#include "ConnectionInfoJson.h"

int main()
{
    ConnectionInfo ci{
        "10.10.10.10",
        "10.10.10.11",
        "pass"
    };

    auto jsonString = DataJson<ConnectionInfo>::ToJson(ci);
    std::cout << jsonString << std::endl;

    auto ci2 = DataJson<ConnectionInfo>::FromJson(jsonString);

    std::cout << (ci == ci2 ? "true" : "false") << std::endl;

    return 0;
}
