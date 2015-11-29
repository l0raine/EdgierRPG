#ifndef SYS_QUEST_H
#define SYS_QUEST_H

#include "System.h"
#include "Components/Quest.h"

namespace sys
{
class Quest : public System<cmp::Quest>
{
    public:
        /** Default constructor */
        Quest();
        /** Default destructor */
        virtual ~Quest();

        virtual void update(float dt){}
    protected:
    private:
};
}
#endif // SYS_QUEST_H
