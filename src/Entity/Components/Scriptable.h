#ifndef CMP_SCRIPTABLE_H
#define CMP_SCRIPTABLE_H

#include "Component.h"

namespace cmp
{
class Scriptable : public Component
{
    public:
        /** Default constructor */
        Scriptable(unsigned int i);
        /** Default destructor */
        virtual ~Scriptable();

        virtual std::map<std::string, std::string> serialize() const{}
        virtual void unserialize(const std::map<std::string, std::string>& variables){}

        static constexpr Component::Type type()
        {
            return Component::Type::Scriptable;
        }
    protected:
    private:
};
}
#endif // CMP_SCRIPTABLE_H
