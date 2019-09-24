#pragma once

#ifndef CPR_EXAMPLE_HTTP_HPP
#define CPR_EXAMPLE_HTTP_HPP

#define TELEGRAM_API_URL "https://api.telegram.org/bot"
#define LUA_BOT_DATA_TABLE "TelegramBot_Data"

#include <string>
#include <maakinohBot/models/chat.hpp>

namespace MaakinohBot::Telegram::Http{

    void sendMessage(std::string token, int chat_id, std::string text);

     Models::Chat getChat(std::string token, std::string chatName);


}


#endif //CPR_EXAMPLE_HTTP_HPP
