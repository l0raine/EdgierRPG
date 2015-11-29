#ifndef SYS_SKILLTREE_H
#define SYS_SKILLTREE_H

#include "System.h"
#include "Components/SkillTree.h"

namespace sys
{
class SkillTree : public System<cmp::SkillTree>
{
    public:
        /** Default constructor */
        SkillTree();
        /** Default destructor */
        virtual ~SkillTree();

        virtual void update(float dt){}
    protected:
    private:
};
}
#endif // SYS_SKILLTREE_H
