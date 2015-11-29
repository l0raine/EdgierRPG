#include "AnimatedTile.h"

#include "Map/StaticTile.h"
#include "Resources/ResourceManager.h"
#include "Utils/Globals.h"

AnimatedTile::AnimatedTile()
{
	//Setup sprite vertex array
	frameVertexArray = nullptr;
	isTileAnimated = true;
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

void AnimatedTile::update()
{
	//Increase current frame if the frame needs moved on
	//If the currentFrame counter exceeds the number of frames, set it to 0
	if(updateClock.getElapsedTime().asMilliseconds() > switchInterval)
	{
		currentFrame++;
		if(currentFrame >= frames.size())
			currentFrame = 0;
		setTextureRect(frames[currentFrame]);
		updateClock.restart();
	}
}

sf::Vertex *AnimatedTile::getQuad()
{
	return frameVertexArray;
}

sf::IntRect AnimatedTile::getFrame(unsigned int frameIndex)
{
	return frames[frameIndex];
}

unsigned int AnimatedTile::getFrameCount()
{
	return frames.size();
}

unsigned int AnimatedTile::getSwitchInterval()
{
	return switchInterval;
}

void AnimatedTile::setQuad(sf::Vertex* quad)
{
    frameVertexArray = quad;
    updateQuadPosition();
    updateProjectedTexture();
}
