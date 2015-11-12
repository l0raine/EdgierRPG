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
    //Increase current frame if the frame needs moved on
    //If the currentFrame counter exceeds the number of frames, set it to 0
    if(updateClock.getElapsedTime().asMilliseconds() > switchInterval)
    {
        currentFrame++;
        if(currentFrame >= frames.size())
            currentFrame = 0;
        sprite.setTextureRect(frames[currentFrame]);
        updateClock.restart();
    }
}

void AnimatedTile::rotate(int degrees)
{
    sprite.rotate(degrees);
}

int AnimatedTile::getRotation()
{
    return rotation;
}

void AnimatedTile::setRotation(int &newRotation)
{
    rotation = newRotation;

    //Set its center to the sprite's center and not top-left, for rotation.


    //Rotate
    switch(rotation)
    {
        case 0:
            sprite.rotate(0); //Don't rotate - retain original orientation.
            break;
        case 1:
            sprite.rotate(90);
            sprite.setPosition(sprite.getPosition().x + 32, sprite.getPosition().y);
            break;
        case 2:
            sprite.setOrigin(0,32);
            sprite.rotate(180);
            sprite.setPosition(sprite.getPosition().x + 32, sprite.getPosition().y);
            break;
        case 3:
            sprite.setOrigin(0,32);
            sprite.rotate(270);
            sprite.setPosition(sprite.getPosition().x + 32, sprite.getPosition().y + 32);
            break;
        default:
            std::cout<<"Invalid rotation value."<<std::endl;
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
