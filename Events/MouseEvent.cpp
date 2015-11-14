#include "MouseEvent.h"

MouseEvent::MouseEvent(sf::Mouse::Button buttonType, bool isKeyPress, const sf::Vector2i &mousePos)
: MessageBase(Types::mouseEvent)
{
    isPress = isKeyPress;
    this->buttonType = buttonType;
    mousePosition = mousePos;
}

MouseEvent::~MouseEvent()
{
    //dtor
}

std::unique_ptr<MouseEvent> MouseEvent::make(sf::Mouse::Button button, bool isPress, const sf::Vector2i &mousePos)
{
    return std::unique_ptr<MouseEvent>(new MouseEvent(button, isPress, mousePos));
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
