#include "Script.hpp"

#include <SFML/System/Vector2.hpp>

void setClasses(lna::State& state);

Script::Script()
{
    luaState.openLib("base", luaopen_base);
    luaState.openLib("math", luaopen_math);
    luaState.openLib("string", luaopen_string);
    luaState.openLib("table", luaopen_table);

    setClasses(luaState);
}

bool Script::openFile(const std::string& file)
{
    if(luaState.loadFile(file) != LUA_OK)
    {
        // log luaState.getErrors()
        return false;
    }

    if(luaState.run() != LUA_OK)
    {
        // log luaState.getErrors()
        return false;
    }

    return true;
}

void setClasses(lna::State& state)
{
    // all classes that should be visible in Lua should be added here

    /* example with sf::Vector2f */

    // template arguments: ClassType, constructor arguments (none for an empty constructor)
    // function arguments: name of variable in Lua, C++ member pointer, ...
    //state["Vector2f"].setClass<sf::Vector2f, float, float>("x", &sf::Vector2f::x, "y", &sf::Vector2f::y);
}
