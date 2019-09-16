#pragma once


#include <string>

namespace MaakinohBot::Models{

    class ParseableObject{
    public:
        virtual void parse(std::string jsonString){};
    };

}