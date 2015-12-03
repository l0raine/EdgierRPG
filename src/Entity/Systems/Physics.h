#ifndef SYS_PHYSICS_H
#define SYS_PHYSICS_H

#include "System.h"
#include "Components/Physics.h"
#include "ControllerInput.h"
#include "Messaging/MessageBase.h"
#include "Messaging/MessageHandler.h"
#include "Events/EntityEvents/EntityDrawEvent.h"

namespace sys
{
class Physics : public System<cmp::Physics>
{
    public:
        /** Default constructor */
        Physics();
        /** Default destructor */
        virtual ~Physics();

        virtual void update(float dt);
        virtual void handleMessage(std::unique_ptr<MessageBase> message);
    protected:
    private:
        System<cmp::ControllerInput> *controllerSystem;
};
}
#endif // SYS_PHYSICS_H
