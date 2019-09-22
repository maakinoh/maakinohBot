#pragma once

#ifndef MODELS_CHAT_HPP
#define MODELS_CHAT_HPP

#include <maakinohBot/models/parseable_object.hpp>
#include <string>

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

    class SuperGroup : Chat
    {
    public:
        std::string title;

    };

}

#endif