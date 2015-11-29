#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Messaging/MessageHandler.h"
#include "Events/EventTypes.h"
#include "Utils/Globals.h"
#include "Camera/GameCamera.h"


class InputHandler
{
public:

    //Virtual destructor
    virtual ~InputHandler();

    //Get instance for singleton
    static std::shared_ptr<InputHandler> getInstance();

    bool isKeyPressed(sf::Keyboard::Key key); //Check if key is currently pressed
    bool isMousePressed(sf::Mouse::Button button); //Check if key is currently pressed

    void handleEvent(sf::Event event);

protected:
private:

    //Store states of keys; false = released; true = pressed; nullptr = no interaction
    std::map<sf::Keyboard::Key, bool> pressedKeys; //Stores the state of keyboard keys

    //Mouse button states
    bool leftMouse, rightMouse;

    InputHandler();

    //Constructor is private per singleton design
    static std::shared_ptr<InputHandler> instance;

    sf::Event event;


};

#endif // INPUTHANDLER_H
