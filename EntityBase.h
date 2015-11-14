#ifndef ENTITYBASE_H
#define ENTITYBASE_H

#include <string>
#include <SFML/Graphics.hpp>

class EntityBase
{
    public:
        /** Default constructor */
        EntityBase();
        /** Default destructor */
        virtual ~EntityBase();

        sf::VertexArray &getVertexArray(); //For drawing
        sf::Texture *getTexture(); //For texturing the vertex array
    protected:

    private:
        float healthMaximum;
        float healthRemaining;
        float manaMaximum;
        float manaRemaining;

        sf::Vector2f position;
        std::string displayName;
        unsigned int id;
        unsigned int direction;
        unsigned int mapID;

        sf::VertexArray shape; //Temp
        sf::Texture *spriteSheet;
};

#endif // ENTITYBASE_H
