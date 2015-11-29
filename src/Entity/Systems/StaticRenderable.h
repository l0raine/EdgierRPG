#ifndef SYS_STATICRENDERABLE_H
#define SYS_STATICRENDERABLE_H

#include "System.h"
#include "Components/StaticRenderable.h"

namespace sys
{
class StaticRenderable : public System<cmp::StaticRenderable>
{
    public:
        /** Default constructor */
        StaticRenderable();
        /** Default destructor */
        virtual ~StaticRenderable();

        virtual void update(float dt){}
    protected:
    private:
};
}
#endif // SYS_STATICRENDERABLE_H
