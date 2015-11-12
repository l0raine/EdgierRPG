#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include<fstream>

using namespace std;

int main()
{
    sf::Clock loadTime;
    Map aMap("map.txt");
    std::cout << "\nTime taken to load map: " << loadTime.getElapsedTime().asMilliseconds() << "ms";

    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
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
        }
        aMap.update();

        window.clear(sf::Color::Black);
        aMap.draw(window, sf::RenderStates::Default);
        window.display();
    }
    return 0;
}
