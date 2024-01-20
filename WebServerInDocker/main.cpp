#include <iostream>
#include <crow.h>

int main(int argc, char** argv)
{
    auto port = 15800;
    auto env_port = getenv("PORT");
    if (env_port != nullptr)
        port = atoi(env_port);

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    app
        .port(port)
        .multithreaded()
        .run();

    return 0;
}
