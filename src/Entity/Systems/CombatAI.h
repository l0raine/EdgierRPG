#ifndef SYS_COMBATAI_H
#define SYS_COMBATAI_H

#include "System.h"
#include "Components/CombatAI.h"

namespace sys
{
class CombatAI : public System<cmp::CombatAI>
{
    public:
        /** Default constructor */
        CombatAI();
        /** Default destructor */
        virtual ~CombatAI();

        virtual void update(float dt){}
    protected:
    private:
};
}
#endif // SYS_COMBATAI_H
