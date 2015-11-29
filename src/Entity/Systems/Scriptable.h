#ifndef SYS_SCRIPTABLE_H
#define SYS_SCRIPTABLE_H

#include "System.h"
#include "Components/Scriptable.h"

namespace sys
{
class Scriptable : public System<cmp::Scriptable>
{
    public:
        /** Default constructor */
        Scriptable();
        /** Default destructor */
        virtual ~Scriptable();

        virtual void update(float dt){}
    protected:
    private:
};
}
#endif // SYS_SCRIPTABLE_H
