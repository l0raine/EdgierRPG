#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include<fstream>
#include "GUI/GUIManager.h"

using namespace std;

int main()
{
    sf::Vector2i windowSize(800,600);
    sf::Clock loadTime;
    Map aMap("map.txt");
    std::cout << "\nTime taken to load map: " << loadTime.getElapsedTime().asMilliseconds() << "ms\n";

    //Initialize objects
    GUIManager guiManager(windowSize, "quicksand.otf", sf::Color::Yellow, 15);

    //Get instance of gui
    auto gui = *guiManager.getGUIRef();

    //Create a menu to hold our widgets
    auto menu = frd::Maker::make(frd::Menu());

    //Create our first widget
    auto button = frd::Maker::make(frd::Button());
    button->setWidgetInfo("Hello World!", sf::Vector2f(100, 50), sf::Vector2f(100, 100), sf::Color::Blue);
    button->setBezelEnabled(true);
    button->bindFunction(EventTypes::LeftClick_Up, std::bind([&]()
    {
        button->setColor(sf::Color(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
    })); //Bind an event. On left click up, set the button colour to something random.

    //Add the button to the menu, and the menu to the GUI
    menu->addWidget(button);
    gui.addMenu(menu);

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

        //Update FRDGUI for things like animation
        gui.update();
        aMap.update();

        window.clear(sf::Color::Black);
        aMap.draw(window, sf::RenderStates::Default);
        window.draw(gui);
        window.display();
    }
    return 0;
}
