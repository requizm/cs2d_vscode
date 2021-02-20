#ifndef JSONLOADER_H
#define JSONLOADER_H

#include <fstream>
#include <nlohmann/json.hpp>

#include "../Manager/Logger.hpp"


class JSONLoader
{
   private:
   public:
    JSONLoader();
    ~JSONLoader();

    nlohmann::json Load(std::string str);
};

#endif  // JSONLOADER_H