#include <maakinohBot/plugin/plugin_handler.hpp>

using namespace MaakinohBot::Plugin;

int getMsg(lua_State *){

}
void PluginHandler::handle_lua(std::string lua_script, MaakinohBot::Telegram::Bot &telebot, std::string message)
{

    luaL_dostring(this->lua_stack, lua_script.c_str());
    lua_getglobal(this->lua_stack, "OnCommand");
    lua_pushstring(this->lua_stack, message.c_str());

    lua_pcall(this->lua_stack, 1,0,0);

    lua_newtable(this->lua_stack);
    int a = lua_gettop(this->lua_stack);

    /* -2 lua_stack*/lua_setglobal(this->lua_stack , "Message");
    /* -1 lua stack*/lua_pushcfunction(this->lua_stack, getMsg);
    lua_setfield(this->lua_stack, -2, "GetMsg");

}

PluginHandler::PluginHandler()
{
    this->lua_stack = luaL_newstate();
}


