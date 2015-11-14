#ifndef ENTITYANIMATION_H
#define ENTITYANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>

class EntityAnimation
{
    public:
        /** Default constructor */
        EntityAnimation();
        /** Default destructor */
        virtual ~EntityAnimation();

        //Animation related
        void addFrame(unsigned int direction, const sf::IntRect &frameData);
        void setDirection(unsigned int direction);
        void stop();
        void start();
        unsigned int getDirection();
        void setFrameInterval(unsigned int interval);
        unsigned int getFrameInterval();
        void update();
        bool isAnimationRunning();

        //Vertex array related
        void setTexture(sf::Texture *texture);
        void setPosition(const sf::Vector2f &newPosition);
        void setPosition(float x, float y);
        void draw(sf::RenderTarget &target);
        void setTextureRect(const sf::IntRect &newRect);
        const sf::IntRect &getTextureRect();
        const sf::FloatRect &getGlobalBounds();
    protected:
    private:
        //Animation related
        std::vector<sf::IntRect> frames[4]; //4 lots of frames, one for each direction. (Frame Offset, Frame Size)
        unsigned int currentFrame;
        sf::Clock updateClock;
        unsigned int switchInterval;
        bool isRunning;

        //Vertex array related
        unsigned int currentDirection; //0 = up, 1 = down, 2 = right, 3 = left
        sf::Texture *frameTexture;
        sf::VertexArray sprite;
        sf::Vector2f position;
        sf::IntRect textureRect;
        sf::FloatRect tileRect;

        void updateProjectedTexture(); //Updates the texture projection
        void updateQuadPosition(); //Updates the quad's position
};

#endif // ENTITYANIMATION_H
