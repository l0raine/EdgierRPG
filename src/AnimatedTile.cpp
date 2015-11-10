#include "AnimatedTile.h"

AnimatedTile::AnimatedTile()
{
    //ctor
}

AnimatedTile::~AnimatedTile()
{
    //dtor
}

void AnimatedTile::setSwitchInterval(int switchIntervalNew)
{
    switchInterval = switchIntervalNew;
}

void AnimatedTile::addFrame(const sf::IntRect &frameRect)
{
    frames.emplace_back(frameRect);
}

void AnimatedTile::setTexture(sf::Texture* texture)
{
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(0,0,0,0));
}

void AnimatedTile::update()
{
    if(updateClock.getElapsedTime().asMilliseconds() > switchInterval)
    {
        currentFrame++;
        if(currentFrame >= frames.size())
            currentFrame = 0;
        sprite.setTextureRect(frames[currentFrame]);
        updateClock.restart();
    }
}

void AnimatedTile::setPosition(const sf::Vector2f newPosition)
{
    sprite.setPosition(newPosition);
}

void AnimatedTile::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

void AnimatedTile::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
    target.draw(sprite, states);
}
