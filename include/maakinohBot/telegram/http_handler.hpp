#ifndef CPR_EXAMPLE_HTTP_HPP
#define CPR_EXAMPLE_HTTP_HPP

#define TELEGRAM_API_URL "https://api.telegram.org/bot"
#include <string>

namespace MaakinohBot::Telegram::Http{

    void sendMessage(std::string token, int chat_id, std::string text);


}


#endif //CPR_EXAMPLE_HTTP_HPP
