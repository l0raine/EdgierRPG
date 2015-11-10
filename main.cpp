#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"

using namespace std;

int main()
{
    Map aMap("map.txt");

    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
    while(window.isOpen())
    {
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
