#ifndef SYS_ANIMATEDRENDERABLE_H
#define SYS_ANIMATEDRENDERABLE_H

#include "System.h"
#include "Components/AnimatedRenderable.h"

namespace sys
{
class AnimatedRenderable : public System<cmp::AnimatedRenderable>
{
    public:
        /** Default constructor */
        AnimatedRenderable();
        /** Default destructor */
        virtual ~AnimatedRenderable();

        virtual void update(float dt){}
    protected:
    private:
};
}
#endif // SYS_ANIMATEDRENDERABLE_H
