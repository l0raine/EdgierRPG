#include "EntityAnimation.h"

EntityAnimation::EntityAnimation()
{
    currentDirection = 0;
    currentFrame = 0;
    isRunning = true;
    sprite = sf::VertexArray(sf::Quads, 4);
}

EntityAnimation::~EntityAnimation()
{
    //dtor
}

void EntityAnimation::addFrame(unsigned int direction, const sf::IntRect &frameData)
{
    frames[direction].emplace_back(frameData);
}

void EntityAnimation::setDirection(unsigned int direction)
{
    currentDirection = direction;

    //As the frame count of each direction may differ, ensure that the current frame is still within valid bounds
    if(currentFrame >= frames[currentFrame].size())
        currentFrame = 0;
}

void EntityAnimation::stop()
{
    isRunning = false;
}

void EntityAnimation::start()
{
    isRunning = true;
}

unsigned int EntityAnimation::getDirection()
{
    return currentDirection;
}

void EntityAnimation::setFrameInterval(unsigned int interval)
{
    switchInterval = interval;
}

unsigned int EntityAnimation::getFrameInterval()
{
    return switchInterval;
}

void EntityAnimation::update()
{
    if(updateClock.getElapsedTime().asMilliseconds() > static_cast<int>(switchInterval))
    {
        currentFrame++;
        if(currentFrame >= frames[currentDirection].size())
            currentFrame = 0;
        setTextureRect(frames[currentDirection][currentFrame]);
        updateQuadPosition();
        updateClock.restart();
    }

}

void EntityAnimation::setTexture(sf::Texture *texture)
{
    frameTexture = texture;
}

void EntityAnimation::setPosition(const sf::Vector2f &newPosition)
{
    //Update position
    position = newPosition;

    //Update global bounds
    tileRect.left = newPosition.x;
    tileRect.top = newPosition.y;
    tileRect.width = 32;
    tileRect.height = 32;

    //Update quad position
    updateQuadPosition();
}

void EntityAnimation::setPosition(float x, float y)
{
    setPosition(sf::Vector2f(x, y));
}

void EntityAnimation::updateProjectedTexture()
{
    sprite[1].texCoords = sf::Vector2f(textureRect.left, textureRect.top);
    sprite[2].texCoords = sf::Vector2f(textureRect.left + frames[currentDirection][currentFrame].width , textureRect.top );
    sprite[3].texCoords = sf::Vector2f(textureRect.left + frames[currentDirection][currentFrame].width, textureRect.top  + frames[currentDirection][currentFrame].height);
    sprite[0].texCoords = sf::Vector2f(textureRect.left, textureRect.top  + frames[currentDirection][currentFrame].height);
}

void EntityAnimation::updateQuadPosition()
{
    //Update the quads position
    sprite[1].position = {tileRect.left , tileRect.top};
    sprite[2].position = {tileRect.left + frames[currentDirection][currentFrame].width , tileRect.top };
    sprite[3].position = {tileRect.left + frames[currentDirection][currentFrame].width, tileRect.top  + frames[currentDirection][currentFrame].height};
    sprite[0].position = {tileRect.left, tileRect.top  + frames[currentDirection][currentFrame].height};
}

void EntityAnimation::setTextureRect(const sf::IntRect &newRect)
{
    textureRect = newRect;
    updateProjectedTexture();
}

const sf::IntRect &EntityAnimation::getTextureRect()
{
    return textureRect;
}

const sf::FloatRect &EntityAnimation::getGlobalBounds()
{
    return tileRect;
}

bool EntityAnimation::isAnimationRunning()
{
    return isRunning;
}

void EntityAnimation::draw(sf::RenderTarget& target)
{
    //Draw current frame to window
    target.draw(sprite, frameTexture);
}
