#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <SFML/Window/Keyboard.hpp>

#include "../MessageBase.h"

class KeyEvent : public MessageBase
{
    public:
        /** Default constructor */
        KeyEvent(bool isKeyPress, sf::Keyboard::Key keyType);
        /** Default destructor */
        virtual ~KeyEvent();

        static std::unique_ptr<KeyEvent> make(bool isKeyPress, sf::Keyboard::Key keyType);
        bool isKeyPress();
        sf::Keyboard::Key getKey();
    protected:
    private:
        bool isPress;
        sf::Keyboard::Key type;
};

#endif // KEYEVENT_H
