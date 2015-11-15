#ifndef HELPERCLASS_H
#define HELPERCLASS_H

#include "Map.h"

class HelperClass
{
    public:
        /** Default constructor */
        HelperClass();
        /** Default destructor */
        virtual ~HelperClass();

        static unsigned int getTileIDFromPosition(const sf::Vector2f &position, Map &theMap);
    protected:
    private:
};

#endif // HELPERCLASS_H
