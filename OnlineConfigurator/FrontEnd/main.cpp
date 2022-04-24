#include "Application.h"

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env)
    {
        return std::make_unique<Application>(env);
    });
}
