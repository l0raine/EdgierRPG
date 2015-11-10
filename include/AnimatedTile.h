#ifndef ANIMATEDTILE_H
#define ANIMATEDTILE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class AnimatedTile
{
    public:
        AnimatedTile();
        virtual ~AnimatedTile();

        void setSwitchInterval(int switchIntervalNew);
        void setTexture(sf::Texture *texture);
        void addFrame(const sf::IntRect &frameRect);
        void update();
        void setPosition(const sf::Vector2f newPosition);
        void setPosition(float x, float y);
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const;
    protected:
    private:
        sf::Sprite sprite;
        unsigned int currentFrame;
        int switchInterval;
        std::vector<sf::IntRect> frames;
        sf::Clock updateClock;
};

#endif // ANIMATEDTILE_H
