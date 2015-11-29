#ifndef CMP_SKILLTREE_H
#define CMP_SKILLTREE_H

#include "Component.h"

namespace cmp
{
class SkillTree : public Component
{
    public:
        /** Default constructor */
        SkillTree(unsigned int i);
        /** Default destructor */
        virtual ~SkillTree();

        virtual std::map<std::string, std::string> serialize() const{}
        virtual void unserialize(const std::map<std::string, std::string>& variables){}

        static constexpr Component::Type type()
        {
            return Component::Type::SkillTree;
        }
    protected:
    private:
};
}
#endif // CMP_SKILLTREE_H
