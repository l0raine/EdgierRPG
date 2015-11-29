#ifndef SYS_PATHFINDINGAI_H
#define SYS_PATHFINDINGAI_H

#include "System.h"
#include "Components/PathfindingAI.h"

namespace sys
{
class PathfindingAI : public System<cmp::PathfindingAI>
{
    public:
        /** Default constructor */
        PathfindingAI();
        /** Default destructor */
        virtual ~PathfindingAI();

        virtual void update(float dt){}
    protected:
    private:
};
}
#endif // SYS_PATHFINDINGAI_H
