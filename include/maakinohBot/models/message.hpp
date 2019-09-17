#pragma once

#include <maakinohBot/models/parseable_object.hpp>
#include <maakinohBot/models/user.hpp>


namespace MaakinohBot::Models
{

    class Message : ParseableObject
    {

    public:
        int message_id;
        User from;
        int date;
    };
}