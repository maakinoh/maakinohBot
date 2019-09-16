#pragma once

#include <maakinohBot/models/parseable_object.hpp>

namespace MaakinohBot::Models{
    class User : public ParseableObject{
    public:
        int id;
        bool is_bot;
        std::string first_name;
        std::string last_name;
        std::string username;
        std::string language_code;

        void parse(std::string jsonString) override;
    };
}