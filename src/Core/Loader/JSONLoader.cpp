#include "JSONLoader.hpp"

#include <fstream>

#include "../Manager/Logger.hpp"

nlohmann::json JSONLoader::Load(std::string str)
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