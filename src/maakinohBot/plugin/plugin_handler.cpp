#include <maakinohBot/plugin/plugin_handler.hpp>
#include <cstdio>
#include <maakinohBot/telegram/http_handler.hpp>

#include <maakinohBot/models/chat.hpp>

using namespace MaakinohBot::Plugin;

int getMsg(lua_State *state)
{

}


int PluginHandler::lua_message_reply(lua_State *L)
{
    lua_gettable(L, -1);
    return 0;
}

int PluginHandler::lua_get_bot_id_from_lua(lua_State *L)
{
    lua_getglobal(L, LUA_BOT_DATA_TABLE);
    lua_getfield(L, -1, "ID");
    lua_tointeger(L, -1);

    return 0;
}

int PluginHandler::lua_find_chat_by_name(lua_State *L)
{
    std::string ChatId = lua_tostring(L, -1);

    lua_getglobal(L, LUA_BOT_DATA_TABLE);
    lua_getfield(L, -1, "ID");

    int telegramBotId = lua_tointeger(L, -1);


    return 1;
}

void add_chat_to_lua_stack(lua_State *L, MaakinohBot::Models::Chat chat)
{
    lua_newtable(L);

    lua_pushinteger(L , chat.id);
    lua_setfield(L, -2, "Id");

    switch (chat.type){
        case CHAT_TYPE_PRIVATE:
            lua_pushstring(L, "Private");
            break;
        case CHAT_TYPE_GROUP:
            lua_pushstring(L, "Group");
            break;
        case CHAT_TYPE_SUPER_GROUP:
            lua_pushstring(L, "SuperGroup");
            break;
        case CHAT_TYPE_CHANNEL:
            lua_pushstring(L, "Channel");
            break;
    }
    lua_setfield(L, -2 , "Type");

}

int PluginHandler::lua_finc_chat_by_id(lua_State *L)
{
    if (lua_isnumber(L, -1) == 1)
    {
        auto id = lua_tonumber(L, -1);

        lua_newtable(L);
        int chatId = 0;
        lua_pushinteger(L, chatId);
        lua_setfield(L, -2, "ID");
    }
    return 1;
}


int PluginHandler::lua_send_message_to_chat_by_id(lua_State *L)
{
    if (lua_isinteger(L, -2) == 1 and lua_isstring(L, -1) == 1)
    {
        int chatId = lua_tointeger(L, -2);
        std::string text = lua_tostring(L, -1);
        Telegram::Http::sendMessage("", chatId, text);
        lua_pushinteger(L, 1);
        return 1;
    }
    lua_pushinteger(L, -1);
    return 1;
}

void PluginHandler::lua_set_bot_data_global(lua_State *L, Telegram::Bot &telebot)
{
    lua_newtable(L); /* {} */

    lua_pushstring(L, std::to_string(telebot.id).c_str()); /* {}, telebotID */
    lua_setfield(L, -1, "ID"); /*{"ID" : telebotID}*/

    lua_setglobal(L, "TelegramBot_Data");
}

void PluginHandler::lua_set_global_telegram_functions()
{
    lua_newtable(this->lua_stack); /* create Telegram Table  ==> stack: ..., {} */
    int telegramTableFind = lua_gettop(this->lua_stack);

    lua_newtable(this->lua_stack); /*stack: ..., {}, {}*/

    lua_pushcfunction(this->lua_stack, this->lua_find_chat_by_name); /* stack: ..., {}, {}, cfnc:lua_find_user_by_id */
    lua_setfield(this->lua_stack, -1, "UserById"); /* stack : ... , {}, {UserById : cfnc:lua_find_user_by_id} */

    lua_pushcfunction(this->lua_stack,
                      this->lua_finc_chat_by_id); /*stack: ..., {}, {UserById : cfnc:lua_find_user_by_id}, cfnc:lua_finc_chat_by_id */
    lua_setfield(this->lua_stack, -1,
                 "ChatById"); /*stack: ... {}, {UserById : cfnc:lua_find_user_by_id, ChatById: cfnc:lua_finc_chat_by_id}*/

    lua_setfield(this->lua_stack, -1,
                 "Find"); /*stack: ..., {Find: {UserById : cfnc:lua_find_user_by_id, ChatById: cfnc:lua_finc_chat_by_id}}*/

    lua_newtable(
            this->lua_stack); /*stack: ..., {Find: {UserById : cfnc:lua_find_user_by_id, ChatById: cfnc:lua_finc_chat_by_id}}, {} */

    lua_pushcfunction(this->lua_stack,
                      this->lua_send_message_to_chat_by_id);  /*stack: ..., {Find: {UserById : cfnc:lua_find_user_by_id, ChatById: cfnc:lua_finc_chat_by_id}}, {}, cfnc:lua_send_message_to_chat_by_id */
    lua_setfield(this->lua_stack, -1,
                 "MessageToChatByID"); /*stack: ..., {Find: {UserById : cfnc:lua_find_user_by_id, ChatById: cfnc:lua_finc_chat_by_id}}, {MessageToChatByID : cfnc:lua_send_message_to_chat_by_id} */

    lua_setglobal(this->lua_stack, "Telegram");
}

void PluginHandler::handle_lua(std::string lua_script, MaakinohBot::Telegram::Bot &telebot, Models::Message &message)
{
    if (this->lua_stack == nullptr)
    {
        return;
    }

    this->lua_set_global_telegram_functions();
    lua_pushcfunction(this->lua_stack, this->lua_send_message_to_chat_by_id);
    lua_setglobal(this->lua_stack, "SendMessageToChatByID");


    luaL_dostring(this->lua_stack, lua_script.c_str());

    /* First push the OnCommand lua function onto the stack */
    int global = lua_getglobal(this->lua_stack, "OnCommand");
    if (global == LUA_OK)
    {
        /* Create the parameter for the lua function as a table*/
        lua_newtable(this->lua_stack);
        int messageTable = lua_gettop(this->lua_stack);
        lua_pushvalue(this->lua_stack, messageTable);

        /*Push a method to the function which reply to the sender of the msg*/
        lua_pushcfunction(this->lua_stack, this->lua_message_reply);
        lua_setfield(this->lua_stack, -2, "Reply");

        /*Push the text of the message to the table*/
        lua_pushstring(this->lua_stack, message.text.c_str());
        lua_setfield(this->lua_stack, -2, "Text");

        lua_pushinteger(this->lua_stack, message.from.id);
        lua_setfield(this->lua_stack, -2, "Author_ID");

        lua_pushinteger(this->lua_stack, message.chat.id);
        lua_setfield(this->lua_stack, -2, "Chat_ID");


        lua_pcall(this->lua_stack, 1, 0, 0);
    }

}

PluginHandler::PluginHandler()
{
    this->lua_stack = luaL_newstate();
}

PluginHandler::~PluginHandler()
{
    lua_close(this->lua_stack);

}
