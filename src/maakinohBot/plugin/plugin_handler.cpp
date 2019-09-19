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

void PluginHandler::handle_lua(std::string lua_script, MaakinohBot::Telegram::Bot &telebot, Models::Message message)
{
    luaL_dostring(this->lua_stack, lua_script.c_str());

    lua_getglobal(this->lua_stack, "OnCommand"); /* First push the OnCommand lua function onto the stack */

    /* Create the parameter for the lua function as a table*/
    lua_newtable(this->lua_stack);
    int a = lua_gettop(this->lua_stack);

    /*Push a method to the function which reply to the sender of the msg*/
    lua_pushcfunction(this->lua_stack, this->lua_message_reply);
    lua_setfield(this->lua_stack, -2, "Reply");

    /*Push the text of the message to the table*/
    lua_pushstring(this->lua_stack, message.text.c_str());
    lua_setfield(this->lua_stack, -2, "Text");



    lua_pcall(this->lua_stack, 1, 0, 0);


}

PluginHandler::PluginHandler()
{
    this->lua_stack = luaL_newstate();
}


