#pragma once

#ifndef PLUGIN_PLUGIN_HANDLER_HPP
#define PLUGIN_PLUGIN_HANDLER_HPP

#include <lua.hpp>
#include <maakinohBot/telegram/bot.hpp>
#include <maakinohBot/models/message.hpp>

#include <string>

namespace MaakinohBot::Plugin
{

    class PluginHandler
    {
    private:
        lua_State *lua_stack;
        void lua_set_global_telegram_functions();

        static int lua_message_reply(lua_State *L);

        static int lua_find_user_by_id(lua_State *L);

        static int lua_finc_chat_by_id(lua_State *L);

        static int lua_send_message_to_chat_by_id(lua_State *L);

        static int lua_get_bot_id_from_lua(lua_State *L);



        void lua_set_bot_data_global(lua_State *L, Telegram::Bot &telebot);

    public:
        PluginHandler();
        ~PluginHandler();

        void handle_lua(std::string lua_script, Telegram::Bot &telebot, Models::Message &message);


    };
}

#endif //PLUGIN_PLUGIN_HANDLER_HPP
