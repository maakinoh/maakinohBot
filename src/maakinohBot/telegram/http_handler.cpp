#include <maakinohBot/telegram/http_handler.hpp>
#include <maakinohBot/models/chat.hpp>
#include <cpr/cpr.h>

void MaakinohBot::Telegram::Http::sendMessage(std::string token, int chat_id, std::string text)
{
    cpr::Post(cpr::Url{TELEGRAM_API_URL + token+"/sendMessage"}, cpr::Payload{{"chat_id", std::to_string(chat_id)},
                                                               {"text",    text}});


}

MaakinohBot::Models::Chat MaakinohBot::Telegram::Http::getChat(std::string token, std::string chatName)
{
    auto res = cpr::Post(cpr::Url{TELEGRAM_API_URL+token+"/getChat"}, cpr::Payload{{"chat_id", chatName}});

    return MaakinohBot::Models::Chat();
}
