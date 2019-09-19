#pragma once

#ifndef PLUGIN_PLUGIN_HANDLER_HPP
#define PLUGIN_PLUGIN_HANDLER_HPP

#include <lua.hpp>
#include <maakinohBot/telegram/bot.hpp>
#include <maakinohBot/models/message.hpp>

#include <string>

namespace MaakinohBot::Plugin{

    class PluginHandler{
    private:
        lua_State* lua_stack;

        static int lua_message_reply(lua_State* lua_stack);
    public:
        PluginHandler();

        void handle_lua(std::string lua_script, Telegram::Bot& telebot, Models::Message message);


    };
}

#endif //PLUGIN_PLUGIN_HANDLER_HPP
