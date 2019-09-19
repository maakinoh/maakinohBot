#include <maakinohBot/plugin/plugin_handler.hpp>

using namespace MaakinohBot::Plugin;

int getMsg(lua_State *state)
{

}

int PluginHandler::lua_message_reply(lua_State *lua_stack)
{
    lua_gettable(lua_stack, -1);
    return 0;
}

int PluginHandler::lua_find_user_by_id(lua_State *lua_stack)
{
    return 0;
}

int PluginHandler::lua_finc_chat_by_id(lua_State *lua_stack)
{
    return 0;
}

int PluginHandler::lua_send_message_to_chat_by_id(lua_State *lua_stack)
{
    return 0;
}

void PluginHandler::handle_lua(std::string lua_script, MaakinohBot::Telegram::Bot &telebot, Models::Message &message)
{
    if (this->lua_stack == nullptr){
        return;
    }

    lua_pushcfunction(this->lua_stack, this->lua_find_user_by_id);
    lua_setglobal(this->lua_stack, "FindUserById");

    lua_pushcfunction(this->lua_stack, this->lua_finc_chat_by_id);
    lua_setglobal(this->lua_stack, "FindChatById");

    lua_pushcfunction(this->lua_stack, this->lua_send_message_to_chat_by_id);
    lua_setglobal(this->lua_stack, "SendMessageToChatByID");


    luaL_dostring(this->lua_stack, lua_script.c_str());

    /* First push the OnCommand lua function onto the stack */
    int global = lua_getglobal(this->lua_stack, "OnCommand");
    if (global == LUA_OK)
    {
        /* Create the parameter for the lua function as a table*/
        lua_newtable(this->lua_stack);
        int a = lua_gettop(this->lua_stack);

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


