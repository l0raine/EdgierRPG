#ifndef SYS_INTERACTABLE_H
#define SYS_INTERACTABLE_H

#include "System.h"
#include "Components/Interactable.h"

namespace sys
{
class Interactable : public System<cmp::Interactable>
{
    public:
        /** Default constructor */
        Interactable();
        /** Default destructor */
        virtual ~Interactable();

        virtual void update(float dt){}
    protected:
    private:
};
}

#endif // SYS_INTERACTABLE_H
