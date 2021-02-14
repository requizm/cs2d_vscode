#ifndef JSONLOADER_H
#define JSONLOADER_H

#include <nlohmann/json.hpp>
#include <fstream>

#include "../Manager/Logger.hpp"

class JSONLoader
{
private:
public:
    JSONLoader();
    ~JSONLoader();

    nlohmann::json Load(std::string str);
};

#endif // JSONLOADER_H