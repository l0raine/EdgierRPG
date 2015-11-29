#ifndef SYS_COMBAT_H
#define SYS_COMBAT_H

#include "System.h"
#include "Components/Combat.h"

namespace sys
{
class Combat : public System<cmp::Combat>
{
    public:
        /** Default constructor */
        Combat();
        /** Default destructor */
        virtual ~Combat();

        virtual void update(float dt){}
    protected:
    private:
};
}
#endif // SYS_COMBAT_H
