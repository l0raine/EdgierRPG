#include "EntityAnimation.h"

EntityAnimation::EntityAnimation()
{
    currentDirection = 0;

}

EntityAnimation::~EntityAnimation()
{
    //dtor
}

void EntityAnimation::addFrame(unsigned int direction, const sf::IntRect &frameData)
{
    frames[direction].emplace_back(frameData);
}
