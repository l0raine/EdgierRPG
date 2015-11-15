#include "InputHandler.h"
#include "MessageHandler.h"
#include "EventTypes.h"
#include <iostream>

std::shared_ptr<InputHandler> InputHandler::instance;

InputHandler::InputHandler()
{
    //ctor
    rightMouse = false;
    leftMouse = false;
}

InputHandler::~InputHandler()
{
    //dtor
}

std::shared_ptr<InputHandler> InputHandler::getInstance()
{
    if(instance == nullptr)
    {
        instance = std::shared_ptr<InputHandler>(new InputHandler);
    }
    return instance;
}

bool InputHandler::isKeyPressed(sf::Keyboard::Key key)
{
    return pressedKeys[key];
}

void InputHandler::handleEvent(const sf::Event event)
{
    //Process key events such as pressing and releasing
    if(event.type == sf::Event::KeyPressed)
    {
        pressedKeys[event.key.code] = true;
        MessageHandler::getInstance()->dispatch(KeyEvent::make(true, event.key.code));
    }
    if(event.type == sf::Event::KeyReleased)
    {
        pressedKeys[event.key.code] = false;
        MessageHandler::getInstance()->dispatch(KeyEvent::make(false, event.key.code));
    }

    //Process mouse events such as Left mouse click, right mouse click
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            leftMouse = true;
            MessageHandler::getInstance()->dispatch(MouseEvent::make(sf::Mouse::Left, true, sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
        }
        if(event.mouseButton.button == sf::Mouse::Right)
        {
            rightMouse = true;
            MessageHandler::getInstance()->dispatch(MouseEvent::make(sf::Mouse::Right, true, sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
        }
    }
    else if(event.type == sf::Event::MouseButtonReleased)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            leftMouse = false;
            MessageHandler::getInstance()->dispatch(MouseEvent::make(sf::Mouse::Left, false, sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
        }
        if(event.mouseButton.button == sf::Mouse::Right)
        {
            rightMouse = false;
            MessageHandler::getInstance()->dispatch(MouseEvent::make(sf::Mouse::Right, false, sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
        }
    }
    //Add possible middle mouse support
}

bool InputHandler::isMousePressed(sf::Mouse::Button button)
{
    if(button == sf::Mouse::Left && leftMouse)
        return true;
    else if(button == sf::Mouse::Right && rightMouse)
        return true;
    return false;
}
