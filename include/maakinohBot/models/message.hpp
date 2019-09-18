#pragma once

#ifndef MODELS_MESSAGE_HPP
#define MODELS_MESSAGE_HPP

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

#endif