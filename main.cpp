#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include <fstream>
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

using namespace std;

int main()
{
    sf::Clock loadTime;
    Map aMap;
    if(!aMap.load("./Files/Maps/test_level.txt"))
        std::cout<<"Map failed to load.\n";
    std::cout << "\nTime taken to load map: " << loadTime.getElapsedTime().asMilliseconds() << "ms\n";

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
        unsigned int tileCount = aMap.getTileCount(0); //Get the number of tiles on this layer
        for(unsigned int tileID = 0; tileID < tileCount; tileID++) //Loop through each loaded tile
        {
            TileBase *tile = aMap.getTile(0, tileID); //Get a pointer to the current tile
            tile->setTextureRect(sf::IntRect(0, 0, 32, 32)); //Set a new texture
        }
        std::cout << "\nMap transformation took: " << clock.getElapsedTime().asMilliseconds() << "ms";


    })); //Bind an event. On left click up, set the button colour to something random.

    //Add the button to the menu, and the menu to the GUI
    menu->addWidget(button);
    gui.addMenu(menu);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////TEMPORARY
    sf::Texture *text = ResourceManager::getInstance()->loadTexture("tilesheets/LX.png");
    std::unique_ptr<EntityBase> entity(new EntityBase());
    entity->sprite.addFrame(0, sf::IntRect(495,404,27,42));
    entity->sprite.addFrame(0, sf::IntRect(522,404,23,42));
    entity->sprite.addFrame(0, sf::IntRect(545,404,23,42));

    entity->sprite.addFrame(1, sf::IntRect(495,447,28,41));
    entity->sprite.addFrame(1, sf::IntRect(522,447,26,41));
    entity->sprite.addFrame(1, sf::IntRect(546,447,26,41));

    entity->sprite.addFrame(2, sf::IntRect(495,531,18,40));
    entity->sprite.addFrame(2, sf::IntRect(513,530,20,40));
    entity->sprite.addFrame(2, sf::IntRect(533,529,21,40));

    entity->sprite.addFrame(3, sf::IntRect(495,489,18,40));
    entity->sprite.addFrame(3, sf::IntRect(513,489,20,40));
    entity->sprite.addFrame(3, sf::IntRect(533,489,21,40));


    entity->sprite.addSpecialFrame(0, 0, sf::IntRect(572,447,28,41));
    entity->sprite.addSpecialFrame(0, 0, sf::IntRect(600,447,26,41));
    entity->sprite.addSpecialFrame(0, 0, sf::IntRect(625,447,26,41));

    entity->sprite.setPosition(rand() % 800 + 0, rand() % 600 + 0);
    entity->sprite.setDirection(1);
    entity->sprite.setFrameInterval(100);
    entity->sprite.setTexture(text);
    EntityManager::getInstance()->registerEntity(entity);

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "EdgierRPG - Extremely Early Alpha");
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

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

        std::unique_ptr<MessageBase> message;
        while(MessageHandler::getInstance()->acquire(message))
        {
            //Let game objects process the event
            EntityManager::getInstance()->handleMessage(message);

            switch(message->getMessageType())
            {
                case MessageBase::Types::mouseEvent:
                {
                    MouseEvent* event = dynamic_cast<MouseEvent*>(message.get());
                    break;
                }
                default:
                    break;
            }
        }

        //Update FRDGUI for things like animation
        gui.update();
        aMap.update();
        EntityManager::getInstance()->update();

        window.clear(sf::Color::Black);
        aMap.draw(window, sf::RenderStates::Default);
        EntityManager::getInstance()->draw(window, sf::RenderStates::Default);
        window.draw(gui);
        window.display();
    }
    //aMap.save("./Files/Maps/savedMap.txt");
    return 0;
}
