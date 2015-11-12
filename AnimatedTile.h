#ifndef ANIMATEDTILE_H
#define ANIMATEDTILE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "TileBase.h"

class AnimatedTile : public TileBase
{
    public:
        /** Default constructor */
        AnimatedTile();
        /** Default destructor */
        virtual ~AnimatedTile();

        virtual sf::Vertex *getQuad();
        virtual void setQuad(sf::Vertex *quad);
        virtual void draw(sf::RenderTarget &target, const sf::RenderStates &states);

        void setSwitchInterval(int switchIntervalNew);
        void setTexture(sf::Texture *texture);
        void addFrame(const sf::IntRect &frameRect);
        void update();

        virtual void setPosition(const sf::Vector2f newPosition);
        virtual void setPosition(float x, float y);
        virtual void setRotation(int &newRotation);
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
