#include "MouseEvent.h"

MouseEvent::MouseEvent(sf::Mouse::Button buttonType, bool isKeyPress, const sf::Vector2i &mousePos)
: MessageBase(Types::mouseEvent)
{
    isPress = isKeyPress;
    this->buttonType = buttonType;
    mousePosition = mousePos;
}

MouseEvent::MouseEvent(const sf::Vector2i &mousePos)
 : MessageBase (Types::mouseMoveEvent)
{
    mousePosition = mousePos;
}

MouseEvent::MouseEvent(sf::Mouse::Button button, const sf::Vector2i &mousePos)
 : MessageBase (Types::mouseDragEvent)
{
    mousePosition = mousePos;
    buttonType = button;
}

MouseEvent::~MouseEvent()
{
    //dtor
}

std::unique_ptr<MouseEvent> MouseEvent::make(sf::Mouse::Button button, bool isPress, const sf::Vector2i &mousePos)
{
    return std::unique_ptr<MouseEvent>(new MouseEvent(button, isPress, mousePos));
}

std::unique_ptr<MouseEvent> MouseEvent::make(const sf::Vector2i &mousePos)
{
    return std::unique_ptr<MouseEvent>(new MouseEvent(mousePos));
}

std::unique_ptr<MouseEvent> MouseEvent::make(sf::Mouse::Button button, const sf::Vector2i &mousePos)
{
    return std::unique_ptr<MouseEvent>(new MouseEvent(button, mousePos));
}

const sf::Vector2i& MouseEvent::getMousePosition()
{
    return mousePosition;
}

bool MouseEvent::isPressed()
{
    return isPress;
}

sf::Mouse::Button MouseEvent::getType()
{
    return buttonType;
}

unsigned int MouseEvent::getClickedTileID()
{
    return HelperClass::getTileIDFromPosition(sf::Vector2f(mousePosition.x, mousePosition.y));
}
