#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include <fstream>
#include "FRDGUI.h"
#include "GUI/GUIManager.h"
#include "ResourceManager.h"
#include "Globals.h"
#include "MessageHandler.h"

using namespace std;

int main()
{
    sf::Clock loadTime;
    Map aMap;
    if(!aMap.load("./Files/Maps/test_level.txt"))
        std::cout<<"Map failed to load.\n";
    std::cout << "\nTime taken to load map: " << loadTime.getElapsedTime().asMilliseconds() << "ms\n";

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

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "EdgierRPG - Extremely Early Alpha");
    window.setFramerateLimit(60);
    while(window.isOpen())
    {
        window.setFramerateLimit(60);
        window.setVerticalSyncEnabled(true);
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
            //Pass the event to FRDGUI to let the GUI respond to it
            gui.handleEvent(event);
        }

        std::unique_ptr<MessageBase> message;
        while(MessageHandler::getInstance()->acquire(message))
        {
            switch(message->getType())
            {
            default:
                std::cout << "\nUnknown message dispatched!";
            }
        }

        //Update FRDGUI for things like animation
        gui.update();
        aMap.update();

        window.clear(sf::Color::Black);
        aMap.draw(window, sf::RenderStates::Default);
        window.draw(gui);
        window.display();
    }
    //aMap.save("./Files/Maps/savedMap.txt");
    return 0;
}
