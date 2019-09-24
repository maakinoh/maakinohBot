#pragma once

#ifndef MODELS_CHAT_HPP
#define MODELS_CHAT_HPP

#include <maakinohBot/models/parseable_object.hpp>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#define CHAT_TYPE_PRIVATE  0
#define CHAT_TYPE_GROUP  1
#define CHAT_TYPE_SUPER_GROUP  2
#define CHAT_TYPE_CHANNEL  3

namespace MaakinohBot::Models
{
    class Chat : ParseableObject
    {
    public:
        int id;
        int type;
    private:
        void parse(std::string jsonString) override;

    };



    int type_string_to_int(std::string i){
        if(i.compare("private") == 0){
            return CHAT_TYPE_PRIVATE;
        } else if(i.compare("group") == 0){
            return CHAT_TYPE_GROUP;
        } else if(i.compare("supergroup") == 0){
            return CHAT_TYPE_SUPER_GROUP;
        } else if(i.compare("channel") == 0){
            return CHAT_TYPE_CHANNEL;
        }
        return -1;
    }

    inline void to_json(json &j, const Chat &p)
    {
        j = json{{"id", p.id},
                 {""}};
    }

    inline void from_json(const json &j, Chat &p)
    {

    }

    class SuperGroup : Chat
    {
    public:
        std::string title;

    };

}

#endif