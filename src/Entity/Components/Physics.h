#ifndef CMP_PHYSICS_H
#define CMP_PHYSICS_H

#include "Component.h"

namespace cmp
{
class Physics : public Component
{
    public:
        /** Default constructor */
        Physics(unsigned int i);
        /** Default destructor */
        virtual ~Physics();

        virtual std::map<std::string, std::string> serialize() const{}
        virtual void unserialize(const std::map<std::string, std::string>& variables){}

        static constexpr Component::Type type()
        {
            return Component::Type::Physics;
        }
    protected:
    private:
};
}
#endif // CMP_PHYSICS_H
