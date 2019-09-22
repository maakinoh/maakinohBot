#include <maakinohBot/telegram/http_handler.hpp>
#include <cpr/cpr.h>

void MaakinohBot::Telegram::Http::sendMessage(std::string token, int chat_id, std::string text)
{
    cpr::Post(cpr::Url{TELEGRAM_API_URL + token}, cpr::Payload{{"chat_id", chat_id},
                                                               {"text",    text}});
}