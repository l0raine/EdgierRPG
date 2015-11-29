#ifndef CMP_QUEST_H
#define CMP_QUEST_H

#include "Component.h"

namespace cmp
{
class Quest : public Component
{
    public:
        /** Default constructor */
        Quest(unsigned int i);
        /** Default destructor */
        virtual ~Quest();

        virtual std::map<std::string, std::string> serialize() const{}
        virtual void unserialize(const std::map<std::string, std::string>& variables){}

        static constexpr Component::Type type()
        {
            return Component::Type::Quest;
        }
    protected:
    private:
};
}
#endif // CMP_QUEST_H
