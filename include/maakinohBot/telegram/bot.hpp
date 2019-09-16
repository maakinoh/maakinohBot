#pragma once

#include <maakinohBot/models/user.hpp>

namespace MaakinohBot::Telegram{

    class Bot{

    public:
        void startBot();
        Models::User get_self();
    };

}