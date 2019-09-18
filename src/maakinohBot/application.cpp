

#include <iostream>
#include <future>
#include <chrono>
#include <thread>

#include <cpr/cpr.h>

#include <nlohmann/json.hpp>
#include <maakinohBot/models/user.hpp>
#include <maakinohBot/telegram/bot.hpp>


using json = nlohmann::json;

void startThread(MaakinohBot::Telegram::Bot &bot)
{
    while (bot.thread_isrunning)
    {

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main(int argc, char **argv)
{
    auto response = cpr::Get(cpr::Url{"https://httpbin.org/get"});
    auto json = json::parse(response.text);
    std::cout << json.dump(4) << std::endl;
    MaakinohBot::Telegram::Bot a = MaakinohBot::Telegram::Bot();

    std::async(startThread, std::ref(a));

}
