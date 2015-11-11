#ifndef STATICTILE_H
#define STATICTILE_H

#include <SFML/Graphics.hpp>

class StaticTile
{
    public:
        /** Default constructor */
        StaticTile();
        /** Default destructor */
        virtual ~StaticTile();

        //SFML-like functions
        const sf::Vector2f &getPosition();
        void setPosition(const sf::Vector2f &newPos);
        void setPosition(float x, float y);
        const sf::FloatRect &getGlobalBounds();
        void setTextureRect(const sf::IntRect &newRect);
        const sf::IntRect &getTextureRect();
    protected:
    private:
        sf::Vector2f position;
        sf::FloatRect floatRect;
        sf::IntRect intRect;
};

#endif // STATICTILE_H
