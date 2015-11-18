#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <Theme.h>

#include "Map.h"
#include "FRDGUI.h"
#include "GUI/GUIManager.h"
#include "ResourceManager.h"
#include "Globals.h"
#include "MessageBase.h"
#include "MessageHandler.h"
#include "SoundHandler.h"
#include "EventTypes.h"
#include "EntityManager.h"
#include "InputHandler.h"
#include "MapManager.h"
#include "HelperClass.h"
#include "SpecialTileContainer.h"
#include "Editor.h"
#include "GameCamera.h"
#include "Player.h"
#include "EntityBase.h"
#include "TileBase.h"

using namespace std;

int main()
{
    //frd::Theme theme(sf::Vector2f(116, 34), sf::Color(0, 102, 0), 11, sf::Color::White, true, sf::Color(90,97,105), sf::Color::Black, 2, sf::Vector2f(900, 900), sf::Vector2f(0,0), "", "");
    //theme.save("myTheme.txt");
/*
    Map test;
    test.setMapSize({500, 500});
    test.setMapName("MyMap");
    test.setAggressiveMusicList({"music1.wav", "music2.wav"});
    test.setAmbientMusicList({"musicPassive1.wav", "musicPassive2.wav"});
    test.save("OUT.txt");
*/

    Editor editor;

    sf::Clock loadTime;
    Map *aMap = MapManager::getInstance()->loadMap("test_level.txt");

    std::cout << "\nTime taken to load map: " << loadTime.getElapsedTime().asMilliseconds() << "ms\n";

     MapManager::getInstance()->setCurrentMap(aMap);

    //Resource/SoundHandler | Sample load for loading sounds
    //ResourceManager::getSoundHandler()->loadMusic("Music/music1.wav", true)
    //ResourceManager::getSoundHandler()->play("Music/music1.wav"

    //Get instance of gui
    auto gui = *GUIManager::getInstance()->getFRDGUIHandle();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////TEMPORARY
    auto menu = frd::Maker::make(frd::Menu());
    auto button = frd::Maker::make(frd::Button());
    button->setWidgetInfo("Don't click me", sf::Vector2f(100, 50), sf::Vector2f(100, 100), sf::Color::Blue); //A blue, 100x50 button positioned at (100, 100) with the label "Hello World!". This function is a shortcut, instead of setting each of these button properties individually
    button->setBezelEnabled(true); //Enable button bezel. Button bezel thickness and colour can be specified with additional function calls.
    button->bindFunction(EventTypes::LeftClick_Up, std::bind([&]()
    {
        sf::Clock clock;
        button->setColor(sf::Color(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));

        //Change tiles on layer 0 to another type
        unsigned int tileCount = MapManager::getInstance()->getCurrentMap()->getTileCount(0); //Get the number of tiles on this layer
        for(unsigned int tileID = 0; tileID < tileCount; tileID++) //Loop through each loaded tile
        {
            TileBase *tile = MapManager::getInstance()->getCurrentMap()->getTile(0, tileID); //Get a pointer to the current tile
            tile->setTextureRect(sf::IntRect(0, 0, 32, 32)); //Set a new texture
        }
        std::cout << "\nMap transformation took: " << clock.getElapsedTime().asMilliseconds() << "ms";


    })); //Bind an event. On left click up, set the button colour to something random.

    //Add the button to the menu, and the menu to the GUI
    menu->addWidget(button);
    gui.addMenu(menu);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////TEMPORARY

    //Create a test entity to roam the map with
    std::unique_ptr<EntityBase> gamePlayer(new Player());
    EntityManager::getInstance()->registerEntity(gamePlayer);

    GameCamera::getInstance()->setFocus(EntityManager::getInstance()->getEntity(EntityManager::getInstance()->getSelectedEntityID()));

    //Define the main render window
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "EdgierRPG - Extremely Early Alpha", sf::Style::Titlebar);
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2,
                                    sf::VideoMode::getDesktopMode().height/4));


    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);

    //Default view
    sf::View defaultView(sf::Vector2f(windowSize.x/2, windowSize.y/2), sf::Vector2f(windowSize.x, windowSize.y));

    //Poll events
    while(window.isOpen())
    {
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
            SpecialTileContainer::getInstance()->handleMessage(message);
            editor.handleMessage(message);


            switch(message->getMessageType())
            {
                case MessageBase::Types::mouseEvent:
                {

                    break;
                }
                default:
                    break;
            }
        }

        //Update FRDGUI for things like animation
        gui.update();

        //Update currently loaded map
        MapManager::getInstance()->getCurrentMap()->update();

        //Update all entities
        EntityManager::getInstance()->update();

        //Update the map editor
        editor.update();

        //Update the game camera
        GameCamera::getInstance()->update();

        //Clear game window to black
        window.clear(sf::Color::Black);

        //Set the window's view to the game camera
        window.setView(GameCamera::getInstance()->getCameraView());

        //Draw the currently Loaded Map
        MapManager::getInstance()->getCurrentMap()->draw(window, sf::RenderStates::Default);

        //Draw all entities
        EntityManager::getInstance()->draw(window, sf::RenderStates::Default);

        //Draw map overlay grid for the editor
        editor.drawMapOverlay(window);

        //Set default view
        window.setView(defaultView);

        //Draw gui elements
        window.draw(gui);

        //Display the window
        window.display();
    }
  //  MapManager::getInstance()->getCurrentMap()->save("./Files/Maps/savedMap.txt");
    return 0;
}
