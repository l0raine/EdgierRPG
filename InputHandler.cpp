#include "InputHandler.h"

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
    for(auto iter = pressedKeys.begin(); iter != pressedKeys.end(); iter++)
    {
        if(iter->first == key)
            return iter->second;
    }
    return false;
}

void InputHandler::handleEvent(sf::Event event)
{
    //If its a mouse related event then offset the event positions by the view offset
    if(event.type == sf::Event::MouseMoved)
    {
        const sf::View &cView = GameCamera::getInstance()->getCameraView();
        event.mouseMove.x += cView.getCenter().x-(windowSize.x/2);
        event.mouseMove.y += cView.getCenter().y-(windowSize.y/2);
    }
    else if(event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
    {
        const sf::View &cView = GameCamera::getInstance()->getCameraView();
        event.mouseButton.x += cView.getCenter().x-(windowSize.x/2);
        event.mouseButton.y += cView.getCenter().y-(windowSize.y/2);
    }

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
        //std::cout<<"Clicked pos: "<<event.mouseButton.x<<", "<<event.mouseButton.y<<" \n";
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            leftMouse = true;
            MessageHandler::getInstance()->dispatch(MouseEvent::make(sf::Mouse::Left, true, gameWindow->mapCoordsToPixel(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))));
        }
        if(event.mouseButton.button == sf::Mouse::Right)
        {
            rightMouse = true;
            MessageHandler::getInstance()->dispatch(MouseEvent::make(sf::Mouse::Right, true, gameWindow->mapCoordsToPixel(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))));
        }
    }
    else if(event.type == sf::Event::MouseButtonReleased)
    {
        //std::cout<<"Released pos: "<<event.mouseButton.x<<", "<<event.mouseButton.y<<" \n";
         sf::IntRect windowRect(sf::Vector2i(0,0), windowSize);
        if(windowRect.contains(event.mouseButton.x, event.mouseButton.y))
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                leftMouse = false;
                MessageHandler::getInstance()->dispatch(MouseEvent::make(sf::Mouse::Left, false, gameWindow->mapCoordsToPixel(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))));
            }
            if(event.mouseButton.button == sf::Mouse::Right)
            {
                rightMouse = false;
                MessageHandler::getInstance()->dispatch(MouseEvent::make(sf::Mouse::Right, false, gameWindow->mapCoordsToPixel(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))));
            }
        }
    }

    //Process mouse click  + drag
    if(event.type == sf::Event::MouseMoved)
    {
        // get the current mouse position in the window
        sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);

        // convert it to world coordinates
        sf::Vector2i worldPos = static_cast<sf::Vector2i>(gameWindow->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)));

        //Get an int rect of the window size
        const sf::IntRect windowRect(sf::Vector2i(0,0), windowSize);

        std::cout<<"Mouse pos: "<<worldPos.x<<", "<<worldPos.y<<" \n";

        if(windowRect.contains(worldPos))
        {
            std::cout<<"Is within window.\n";
            if(leftMouse) //Left click and drag
            {
                MessageHandler::getInstance()->dispatch(MouseEvent::make(sf::Mouse::Left,  worldPos));
            }
            else if(rightMouse) //Right click and drag
            {
                MessageHandler::getInstance()->dispatch(MouseEvent::make(sf::Mouse::Right, worldPos));
            }
        }
    }
}

bool InputHandler::isMousePressed(sf::Mouse::Button button)
{
    if(button == sf::Mouse::Left && leftMouse)
        return true;
    else if(button == sf::Mouse::Right && rightMouse)
        return true;
    return false;
}
