#ifndef STATICTILE_H
#define STATICTILE_H

#include <SFML/Graphics.hpp>

#include "TileBase.h"

class StaticTile : public TileBase
{
public:
    /** Default constructor */
    StaticTile();
    /** Default destructor */
    virtual ~StaticTile();

    virtual sf::Vertex *getQuad();
    virtual void setQuad(sf::Vertex *quad);
    virtual void draw(sf::RenderTarget &target, const sf::RenderStates &states){}; //Stub
protected:
private:
    sf::Vertex *quad; //A pointer to out little quad in the huge map quad

};

#endif // STATICTILE_H
