#pragma once
#ifndef MODELS_PARSEABLE_OBJECT
#define MODELS_PARSEABLE_OBJECT
#include <string>


namespace MaakinohBot::Models{

    class ParseableObject
    {
    public:
        virtual void parse(std::string jsonString){};
    };

}

#endif