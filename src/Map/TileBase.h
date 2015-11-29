#ifndef TILEBASE_H
#define TILEBASE_H

#include <memory>
#include <SFML/Graphics.hpp>

class TileBase
{
public:
    TileBase();
    virtual ~TileBase();
    virtual sf::Vertex *getQuad()=0;
    virtual void setQuad(sf::Vertex *quad)=0;

    void setPosition(const sf::Vector2f &newPosition);
    void setPosition(float x, float y);
    void setRotation(int newRotation);
    void setTextureRect(const sf::IntRect &newRect);
    const sf::IntRect &getTextureRect();
    const sf::FloatRect getGlobalBounds();
    const sf::Vector2f &getPosition();
    bool isAnimated();
    int getRotation();
protected:
    sf::Vector2f position;
    int rotation;
    sf::IntRect textureRect;
    bool isTileAnimated;
    void updateProjectedTexture(); //Updates the texture projection
    void updateQuadPosition(); //Updates the quad's position
private:
};

#endif // TILEBASE_H
