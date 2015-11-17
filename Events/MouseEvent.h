#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <SFML/Window/Mouse.hpp>

#include "../MessageBase.h"
#include "../HelperClass.h"


class MouseEvent : public MessageBase
{
    public:
        /** Default constructor */
        MouseEvent(sf::Mouse::Button keyType, bool isKeyPress, const sf::Vector2i &mousePos);
        /** Default destructor */
        virtual ~MouseEvent();

        static std::unique_ptr<MouseEvent> make(sf::Mouse::Button button, bool isPress, const sf::Vector2i &mousePos);

        const sf::Vector2i& getMousePosition();
        bool isPressed();
        sf::Mouse::Button getType();
        unsigned int getClickedTileID();

    protected:
    private:
        sf::Mouse::Button buttonType;
        bool isPress;
        sf::Vector2i mousePosition;
};

#endif // MOUSEEVENT_H
