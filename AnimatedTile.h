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
		virtual void setQuad(sf::Vertex *quad)
		{} //Stub
		virtual void draw(sf::RenderTarget &target, const sf::RenderStates &states);

		void setSwitchInterval(int switchIntervalNew);
		void addFrame(const sf::IntRect &frameRect);
		sf::IntRect getFrame(unsigned int frameIndex);
		unsigned int getFrameCount();
		void update();
		unsigned int getSwitchInterval();
	
	protected:
	
	private:
		sf::VertexArray frameVertexArray;
		unsigned int currentFrame;
		unsigned int frameCount;
		int switchInterval;
		std::vector<sf::IntRect> frames;
		sf::Clock updateClock;
};

#endif // ANIMATEDTILE_H
