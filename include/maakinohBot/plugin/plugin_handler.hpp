#pragma once

#ifndef PLUGIN_PLUGIN_HANDLER_HPP
#define PLUGIN_PLUGIN_HANDLER_HPP

#include <lua.hpp>
#include <maakinohBot/telegram/bot.hpp>
#include <string>

namespace MaakinohBot::Plugin{

    class PluginHandler{
    public:
        void handle_lua(std::string lua_script, Telegram::Bot& telebot);


    };
}

#endif //PLUGIN_PLUGIN_HANDLER_HPP
