#include "BaseResource.h"

BaseResource::BaseResource(Project& project, const std::string& path, const BaseResourceMethodsConfig& config) :
    _project(project)
{
    set_path(path);
    if (config._get)
        set_method_handler("GET", std::bind(&BaseResource::callbackGet, this, std::placeholders::_1));
    if (config._post)
        set_method_handler("POST", std::bind(&BaseResource::callbackPost, this, std::placeholders::_1));
    if (config._put)
        set_method_handler("PUT", std::bind(&BaseResource::callbackPut, this, std::placeholders::_1));
    if (config._delete)
        set_method_handler("DELETE", std::bind(&BaseResource::callbackDelete, this, std::placeholders::_1));
}
