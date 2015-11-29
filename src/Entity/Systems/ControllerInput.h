#ifndef SYS_CONTROLLERINPUT_H
#define SYS_CONTROLLERINPUT_H

#include "System.h"
#include "Components/ControllerInput.h"

namespace sys
{
class ControllerInput : public System<cmp::ControllerInput>
{
    public:
        /** Default constructor */
        ControllerInput();
        /** Default destructor */
        virtual ~ControllerInput();

        virtual void update(float dt){}
    protected:
    private:
};
}
#endif // SYS_CONTROLLERINPUT_H
