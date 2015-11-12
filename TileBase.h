#ifndef TILEBASE_H
#define TILEBASE_H

#include <SFML/Graphics.hpp>

class TileBase
{
    public:
        TileBase();
        virtual ~TileBase();
        virtual sf::Vertex *getQuad()=0;
        virtual void setQuad(sf::Vertex *quad)=0;

        virtual void setPosition(const sf::Vector2f &newPosition);
        virtual void setPosition(float x, float y);
        virtual void draw(sf::RenderTarget &target, const sf::RenderStates &states)=0;
        virtual void setRotation(int newRotation);
        virtual void setTexture(sf::Texture* newTexture);
        virtual void setTextureRect(const sf::IntRect &newRect);
        virtual const sf::IntRect &getTextureRect();
        virtual const sf::FloatRect &getGlobalBounds();
        int getRotation();
    protected:
        sf::Vector2f position;
        int rotation;
        sf::FloatRect tileRect;
        sf::IntRect textureRect;
        sf::Texture *texture;
        void updateProjectedTexture(); //Updates the texture projection
        void updateQuadPosition(); //Updates the quad's position
    private:
};

#endif // TILEBASE_H
