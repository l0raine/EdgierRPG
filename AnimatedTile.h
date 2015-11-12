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
        virtual void setQuad(sf::Vertex *quad){}; //Stub
        virtual void draw(sf::RenderTarget &target, const sf::RenderStates &states);

        void setSwitchInterval(int switchIntervalNew);
        void addFrame(const sf::IntRect &frameRect);
        void update();
    protected:
    private:
        sf::VertexArray frameVertexArray;
        unsigned int currentFrame;
        int switchInterval;
        std::vector<sf::IntRect> frames;
        int rotation;
        sf::Clock updateClock;
};

#endif // ANIMATEDTILE_H
