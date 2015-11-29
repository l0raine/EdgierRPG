#ifndef SYS_PHYSICS_H
#define SYS_PHYSICS_H

#include "System.h"
#include "Components/Physics.h"

namespace sys
{
class Physics : public System<cmp::Physics>
{
    public:
        /** Default constructor */
        Physics();
        /** Default destructor */
        virtual ~Physics();

        virtual void update(float dt){}
    protected:
    private:
};
}
#endif // SYS_PHYSICS_H
