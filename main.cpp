//STD

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/Lua.hpp>
#include <ZGE/Utility.hpp>
#include <ZGE/State/StateHandler.hpp>
#include <ZGE/State/BaseState.hpp>

//SELF
#include "Player.hpp"
#include "States/SplashState.hpp"

int main()
{
    std::srand(std::time(0));

    zge::Lua LuaState;
    luaL_openlibs(LuaState.getRawState());

    if (LuaState.loadFile("variables.lua")) return 1;
    if (LuaState.executeFile("variables.lua")) return 2;

    sf::RenderWindow window(sf::VideoMode(LuaState.getGlobal<int>("settings.window.w"),
                                          LuaState.getGlobal<int>("settings.window.h"),
                                          LuaState.getGlobal<int>("settings.window.bits")),
                            LuaState.getGlobal<std::string>("settings.window.title"),
                            LuaState.getGlobal<bool>("settings.window.fullscreen") ? sf::Style::Fullscreen : sf::Style::Default);

    {
        int framerate = LuaState.getGlobal<int>("settings.window.framerate");
        if (framerate > 0)
        {
            window.setFramerateLimit(framerate);
        }
    }

    window.setVerticalSyncEnabled(LuaState.getGlobal<bool>("settings.window.verticalSync"));

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
