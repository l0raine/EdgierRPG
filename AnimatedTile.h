#ifndef ANIMATEDTILE_H
#define ANIMATEDTILE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class AnimatedTile
{
    public:
        /** Default constructor */
        AnimatedTile();
        /** Default destructor */
        virtual ~AnimatedTile();

        void setSwitchInterval(int switchIntervalNew);
        void setTexture(sf::Texture *texture);
        void addFrame(const sf::IntRect &frameRect);
        void update();
        void setPosition(const sf::Vector2f newPosition);
        void setPosition(float x, float y);
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const;
        void setRotation(int &newRotation);
        int getRotation();
        void rotate(int degrees);
    protected:
    private:
        sf::Sprite sprite;
        unsigned int currentFrame;
        int switchInterval;
        std::vector<sf::IntRect> frames;
        int rotation;
        sf::Clock updateClock;
};

#endif // ANIMATEDTILE_H
