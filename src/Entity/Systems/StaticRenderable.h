#ifndef SYS_STATICRENDERABLE_H
#define SYS_STATICRENDERABLE_H

#include "System.h"
#include "Components/StaticRenderable.h"
#include "Physics.h"

namespace sys
{
class StaticRenderable : public System<cmp::StaticRenderable>
{
    public:
        /** Default constructor */
        StaticRenderable();
        /** Default destructor */
        virtual ~StaticRenderable();

        void draw(sf::RenderTarget *target) const;

        virtual void update(float dt);
        virtual void handleMessage(std::unique_ptr<MessageBase> message);
    protected:
    private:
        System<cmp::Physics> *physicsSystem;
};
}
#endif // SYS_STATICRENDERABLE_H
