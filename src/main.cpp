#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <Theme.h>

#include "Map/Map.h"
#include "FRDGUI.h"
#include "GUI/GUIManager.h"
#include "Resources/ResourceManager.h"
#include "Utils/Globals.h"
#include "Messaging/MessageBase.h"
#include "Messaging/MessageHandler.h"
#include "Resources/SoundHandler.h"
#include "Events/EventTypes.h"
#include "Entity/EntityManager.h"
#include "Input/InputHandler.h"
#include "Map/MapManager.h"
#include "Utils/HelperClass.h"
#include "Map/SpecialTileContainer.h"
#include "Editor/Editor.h"
#include "Camera/GameCamera.h"
#include "Entity/Player.h"
#include "Entity/EntityBase.h"
#include "Map/TileBase.h"
#include "SystemMap.h"

using namespace std;

int main()
{
    //frd::Theme theme(sf::Vector2f(116, 34), sf::Color(0, 102, 0), 11, sf::Color::White, true, sf::Color(90,97,105), sf::Color::Black, 2, sf::Vector2f(900, 900), sf::Vector2f(0,0), "", "");
    //theme.save("dialogTheme.txt");

    /*Map test;
    test.setMapSize({50, 50});
    test.setMapName("MyMap");
    test.setAggressiveMusicList({"music1.wav", "music2.wav"});
    test.setAmbientMusicList({"musicPassive1.wav", "musicPassive2.wav"});
    test.save("OUT.txt");*/


    Editor &editor = *Editor::getInstance().get();

    sf::Clock loadTime;
    Map *aMap = MapManager::getInstance()->loadMap("test_level.txt");

    std::cout << "\nTime taken to load map: " << loadTime.getElapsedTime().asMilliseconds() << "ms\n";

    MapManager::getInstance()->setCurrentMap(aMap);

    //Resource/SoundHandler | Sample load for loading sounds
    //ResourceManager::getSoundHandler()->loadMusic("Music/music1.wav", true)
    //ResourceManager::getSoundHandler()->play("Music/music1.wav"

    //Get instance of gui
    auto gui = *GUIManager::getInstance()->getFRDGUIHandle();

    //Create a player entity
    std::unique_ptr<EntityBase> gamePlayer(new Player());
    //Register the player
    EntityManager::getInstance()->registerEntity(gamePlayer);

    //Load the editor;
    editor.load();

    //Create the SystemMap object
    SystemMap sysMap;

    GameCamera::getInstance()->setFocus(EntityManager::getInstance()->getEntity(EntityManager::getInstance()->getSelectedEntityID()));

    //Define the main render window
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "EdgierRPG - Extremely Early Alpha", sf::Style::Close);
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2,
                                    sf::VideoMode::getDesktopMode().height/4));


    window.setKeyRepeatEnabled(false);
    gameWindow = &window; //Set the window reference to the main game window

    //Default view
    sf::View defaultView(sf::Vector2f(windowSize.x/2, windowSize.y/2), sf::Vector2f(windowSize.x, windowSize.y));

    //Setup game loop variables
    sf::Clock gameTime;
    const unsigned int frameTime = 1000/60; //60FPS
    double previousFrame = gameTime.getElapsedTime().asMilliseconds();
    double frameLag = 0.0;

    window.setFramerateLimit(144); //To prevent the game from eating CPU cycles. Game will update at same speed regardless of this variable though.

    //Main window loop
    while(window.isOpen())
    {
        //Game loop upkeep
        double currentFrame = gameTime.getElapsedTime().asMilliseconds();
        double elapsedFrame = currentFrame - previousFrame;
        previousFrame = currentFrame;
        frameLag += elapsedFrame;

        //Poll events
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            //Pass the event to FRDGUI to let the GUI respond to it
            gui.handleEvent(event);

            InputHandler::getInstance()->handleEvent(event);
        }

        //Arrest incoming messages and handle them
        std::unique_ptr<MessageBase> message;
        while(MessageHandler::getInstance()->acquire(message))
        {
            //Let game objects process the event
            EntityManager::getInstance()->handleMessage(message);
            MapManager::getInstance()->getCurrentMap()->specialTileContainer.handleMessage(message);
            editor.handleMessage(message);
        }

        //Pass events to the SystemMap


        while(frameLag >= frameTime)
        {
            //Update aspects of the game
            gui.update();
            MapManager::getInstance()->getCurrentMap()->update();
            EntityManager::getInstance()->update();
            editor.update();
            GameCamera::getInstance()->update();

            //Game loop upkeep
            frameLag -= frameTime;
        }

        //Draw current frame
        window.clear(sf::Color::Black);

        //Draw things which belong to game camera
        window.setView(GameCamera::getInstance()->getCameraView());
        MapManager::getInstance()->getCurrentMap()->draw(window, sf::RenderStates::Default);
        EntityManager::getInstance()->draw(window, sf::RenderStates::Default);
        editor.drawMapOverlay(window);

        //Draw things which belong to window camera
        window.setView(defaultView);
        window.draw(gui);

        //Display the frame
        window.display();
    }
    MapManager::getInstance()->getCurrentMap()->save("./Files/Maps/test_level.txt");
    return 0;
}
