#include <iostream>
#include <map>

#define QUIZ(x) void Quiz##x() \
{ \
    std::cout << std::endl << "----" << #x << "----" << std::endl;

#define QUIZ_END \
    std::cout << std::endl << "--------" << std::endl; \
}

QUIZ(207)
    //creating new map item it will be initialized with default ctor or 0
    std::map<int, int> m;
    std::cout << m[42];
QUIZ_END

int main()
{
    Quiz207();

    return 0;
}
