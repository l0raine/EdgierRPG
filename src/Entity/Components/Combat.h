#ifndef CMP_COMBAT_H
#define CMP_COMBAT_H

#include "Component.h"

namespace cmp
{
class Combat : public Component
{
    public:
        /** Default constructor */
        Combat(unsigned int i);
        /** Default destructor */
        virtual ~Combat();

        virtual std::map<std::string, std::string> serialize() const{}
        virtual void unserialize(const std::map<std::string, std::string>& variables){}

        static constexpr Component::Type type()
        {
            return Component::Type::Combat;
        }
    protected:
    private:
};
}
#endif // CMP_COMBAT_H
