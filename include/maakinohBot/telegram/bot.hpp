#pragma once
#ifndef TELEGRAM_BOT_HPP
#define TELEGRAM_BOT_HPP
//#include <maakinohBot/models/user.hpp>

namespace MaakinohBot::Telegram
{

    class Bot
    {

    public:
        bool thread_isrunning;

        void startBot();

        void stopBot();

  //Models::User get_self();
    };

}

#endif