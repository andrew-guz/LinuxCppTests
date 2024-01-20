#include <iostream>
#include <crow.h>

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    app.multithreaded().port(15800).run();

    return 0;
}
