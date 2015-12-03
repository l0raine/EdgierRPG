#ifndef CMP_COMBATAI_H
#define CMP_COMBATAI_H

#include "../Component.h"

namespace cmp
{
class CombatAI : public Component
{
    public:
        /** Default constructor */
        CombatAI(unsigned int i);
        /** Default destructor */
        virtual ~CombatAI();

        virtual std::map<std::string, std::string> serialize() const{}
        virtual void unserialize(const std::map<std::string, std::string>& variables){}

        static constexpr Component::Type type()
        {
            return Component::Type::CombatAI;
        }
    protected:
    private:
};
}
#endif // CMP_COMBATAI_H
