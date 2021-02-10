#include "JSONLoader.hpp"

JSONLoader::JSONLoader()
{
}

JSONLoader::~JSONLoader()
{
}

nlohmann::json JSONLoader::Load(std::string &str)
{
    std::ifstream t(str);
    if (!t)
    {
        WRITE_ERROR("dosya acilamadi: " + str);
        exit(EXIT_FAILURE);
    }

    nlohmann::json j;
    t >> j;

    return j;
}