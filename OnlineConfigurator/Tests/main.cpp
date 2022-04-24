#include <iostream>

#include "Uuid.h"
#include "EntitySerializerFactory.h"
#include "EntitySerializer.h"
#include "ConnectionInformation.h"
#include "Project.h"

int main()
{
    Uuid id;
    std::cout << id.data() << std::endl;

    ConnectionInformation ci;
    //std::cout << "ci true: " << EntitySerializerFactory::instance()->getSerializer(ci.type())->toJson(&ci, true) << std::endl;
    //std::cout << "ci false: " << EntitySerializerFactory::instance()->getSerializer(ci.type())->toJson(&ci, false) << std::endl;

    Project project1;
    //std::cout << "project1 true: " << EntitySerializerFactory::instance()->getSerializer(project1.type())->toJson(&project1, true) << std::endl;
    //std::cout << "project1 false: " << EntitySerializerFactory::instance()->getSerializer(project1.type())->toJson(&project1, false) << std::endl;

    Project project2(false);
    //std::cout << "project2 true: " << EntitySerializerFactory::instance()->getSerializer(project2.type())->toJson(&project2, true) << std::endl;
    //std::cout << "project1 false: " << EntitySerializerFactory::instance()->getSerializer(project2.type())->toJson(&project2, false) << std::endl;

    auto project4 = new Project();;
    std::cout << project4->listSubEntityNames().size() << std::endl;
    auto project4Json = EntitySerializerFactory::instance()->getSerializer(project4->type())->toJson(project4, false);
    delete project4;
    auto project5 = EntitySerializerFactory::instance()->getSerializer(project4Json["type"].get<std::string>())->toEntity(project4Json);
    std::cout << project5->listSubEntityNames().size() << std::endl;
    delete project5;

    return 0;
}
