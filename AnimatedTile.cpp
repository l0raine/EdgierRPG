#include "AnimatedTile.h"

AnimatedTile::AnimatedTile()
{
	//Setup sprite vertex array
	frameVertexArray = sf::VertexArray(sf::Quads, 4);
	isTileAnimated = true;
	frameCount = 0;
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
	frameCount++;
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

void AnimatedTile::draw(sf::RenderTarget &target, const sf::RenderStates &states)
{
	target.draw(frameVertexArray, texture);
}

sf::Vertex *AnimatedTile::getQuad()
{
	return &frameVertexArray[0];
}

sf::IntRect AnimatedTile::getFrame(unsigned int frameIndex)
{
	return frames[frameIndex];
}

unsigned int AnimatedTile::getFrameCount()
{
	return frameCount;
}

unsigned int AnimatedTile::getSwitchInterval()
{
	return switchInterval;
}
