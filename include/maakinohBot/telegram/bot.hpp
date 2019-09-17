#pragma once

#include <maakinohBot/models/user.hpp>

namespace MaakinohBot::Telegram
{

    class Bot
    {

    public:
        bool thread_isrunning;

        void startBot();

        void stopBot();

        Models::User get_self();
    };

}