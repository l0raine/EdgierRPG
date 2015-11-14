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

        void addFrame(unsigned int direction, const sf::IntRect &frameData);

    protected:
    private:
        unsigned int currentDirection; //0 = up, 1 = down, 2 = right, 3 = left
        std::vector<sf::IntRect> frames[4]; //4 lots of frames, one for each direction

};

#endif // ENTITYANIMATION_H
