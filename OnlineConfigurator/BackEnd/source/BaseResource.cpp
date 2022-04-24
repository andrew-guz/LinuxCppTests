#include "BaseResource.h"

BaseResource::BaseResource(Project& project, const std::string& path, const std::string& method) :
    _project(project)
{
    set_path(path);
    set_method_handler("GET", std::bind(&BaseResource::callback, this, std::placeholders::_1));
}
