#pragma once

#include <maakinohBot/models/parseable_object.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace MaakinohBot::Models
{


    class User : public ParseableObject
    {
    public:
        int id;
        bool is_bot;
        std::string first_name;
        std::string last_name;
        std::string username;
        std::string language_code;

        void parse(std::string jsonString) override;
    };

    void to_json(json &j, const User &p)
    {
        j = json{{"id",            p.id},
                 {"is_bot",        p.is_bot},
                 {"first_name",    p.first_name},
                 {"last_name",     p.last_name},
                 {"username",      p.username},
                 {"language_code", p.language_code}};
    }


    void from_json(const json& j, User& p) {
        j.at("name").get_to(p.name);
        j.at("address").get_to(p.address);
        j.at("age").get_to(p.age);
    }

}