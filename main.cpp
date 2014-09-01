//STD

//3RD
#include <SFML/Graphics.hpp>
#include <lua.hpp>
#include <LuaBridge/Luabridge.h>

//SELF
#include "Player.hpp"
#include "ZGE/Utility.hpp"
#include "ZGE/State/StateHandler.hpp"
#include "ZGE/State/BaseState.hpp"
#include "States/SplashState.hpp"

template <typename T>
T getGlobal(lua_State* L, std::string varName)
{
    if (varName.find('.') == std::string::npos)
    {
        luabridge::LuaRef varRef = luabridge::getGlobal(L, varName.c_str());

        if (varRef.isNil())
        {
            throw std::runtime_error(varName + " is Nil");
        }

        return varRef.cast<T>();
    }
    else
    {
        std::stringstream ss(varName);
        std::vector<std::string> vars;
        std::string splitVarName = "";

        while (std::getline(ss, splitVarName, '.'))
        {
            vars.push_back(splitVarName);
        }

        if (vars.size() >= 1)
        {
            luabridge::LuaRef varRef = luabridge::getGlobal(L, vars[0].c_str());

            if (varRef.isNil())
            {
                throw std::runtime_error(vars[0] + " is Nil");
            }

            //std::cout << vars[0] << "\n";

            for (unsigned i = 1; i < vars.size(); ++i)
            {
                //std::cout << vars[i] << "\n";
                varRef = luabridge::LuaRef(varRef[vars[i].c_str()]);

                if (varRef.isNil())
                {
                    throw std::runtime_error(vars[i] + " is Nil");
                }
            }

            return varRef.cast<T>();
        }
        else
        {
            throw std::runtime_error(varName + " is invalid");
        }
    }
}

int luaLoadFile(lua_State* L, std::string file)
{
    int error = luaL_loadfile(L, "variables.lua");

    if (error)
    {
        switch (error)
        {
            case LUA_ERRSYNTAX:
            {
                std::cout << "Syntax Error: " + std::string(lua_tostring(L, -1)) << "\n";
                break;
            }

            case LUA_ERRFILE:
            {
                std::cout << "Could not find file '" << file << "'\n";
                break;
            }

            default:
            {
                std::cout << "ErrorCode = " + zge::toString(error) << "\n";
                break;
            }
        }
    }

    return error;
}

int luaExecuteFile(lua_State* L, std::string file)
{
    int error = lua_pcall(L, 0, 0, 0);

    if (error)
    {
        switch (error)
        {
            case LUA_ERRRUN:
            {
                std::cout << "Runtime Error: " + std::string(lua_tostring(L, -1)) << "\n";
                break;
            }

            case LUA_ERRMEM:
            {
                std::cout << "Memory Allocation Error\n";
                break;
            }

            case LUA_ERRERR:
            {
                std::cout << "Error while running error handler\n";
                break;
            }

            default:
            {
                std::cout << "ErrorCode" + zge::toString(error) << "\n";
            }
        }
    }

    return error;
}

int main()
{
    std::srand(std::time(0));

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if (luaLoadFile(L, "variables.lua")) return 1;
    if (luaExecuteFile(L, "variables.lua")) return 2;

    sf::RenderWindow window(sf::VideoMode(getGlobal<int>(L, "settings.window.w"),
                                          getGlobal<int>(L, "settings.window.h"),
                                          getGlobal<int>(L, "settings.window.bits")),
                            getGlobal<std::string>(L, "settings.window.title"),
                            getGlobal<bool>(L, "settings.window.fullscreen") ? sf::Style::Fullscreen : sf::Style::Default);

    int framerate = getGlobal<int>(L, "settings.window.framerate");
    if (framerate > 0)
    {
        window.setFramerateLimit(framerate);
    }

    window.setVerticalSyncEnabled(getGlobal<bool>(L, "settings.window.verticalSync"));

    zge::StateHandler stateHandler;
    stateHandler.getStateCollection().push<SplashState>(window);

    sf::Clock frameTimer;
    sf::Time prevFrameTime = sf::seconds(1.f/60.f);
    sf::Event event;

    while (window.isOpen() &&
           stateHandler.getStateCollection().getSize() > 0)
    {
        while (window.pollEvent(event))
        {
            stateHandler.handleEvent(event);

            switch(event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    break;
                }

                default:
                {
                    break;
                }
            }
        }

        stateHandler.update(prevFrameTime.asSeconds());

        window.clear(sf::Color(40, 40, 40));
        stateHandler.draw(window);
        window.display();

        stateHandler.postDraw();

        prevFrameTime = frameTimer.restart();
        //std::cout << "FPS: " << 1.f / prevFrameTime.asSeconds() << "\n";
    }

    return 0;
}
