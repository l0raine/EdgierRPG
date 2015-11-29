#include "KeyEvent.h"
#include <iostream>

KeyEvent::KeyEvent(bool isKeyPress, sf::Keyboard::Key keyType)
    : MessageBase(Types::keyEvent)
{
    //ctor
    isPress = isKeyPress;
    type = keyType;
}

KeyEvent::~KeyEvent()
{
    //dtor
}

std::unique_ptr<KeyEvent> KeyEvent::make(bool isKeyPress, sf::Keyboard::Key keyType)
{
    return std::unique_ptr<KeyEvent>(new KeyEvent(isKeyPress, keyType));
}

bool KeyEvent::isKeyPress()
{
    return isPress;
}

sf::Keyboard::Key KeyEvent::getKey()
{
    return type;
}
