#include "UrlBuilder.h"
#include "Application.h"
#include "EntityPool.h"

int main(int argc, char* argv[])
{
    for (auto i = 0; i < argc; ++i)
    {
        if (std::string(argv[i]) == "--backend-port")
        {
            UrlBuilder::instance()->init(atoi(argv[i + 1]));
            break;
        }
    }

    EntityPool::instance()->disable();

    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env)
    {
        return std::make_unique<Application>(env);
    });
}
