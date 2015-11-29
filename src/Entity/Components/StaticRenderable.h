#ifndef CMP_STATICRENDERABLE_H
#define CMP_STATICRENDERABLE_H

#include "Component.h"

namespace cmp
{
class StaticRenderable : public Component
{
    public:
        /** Default constructor */
        StaticRenderable(unsigned int i);
        /** Default destructor */
        virtual ~StaticRenderable();

        virtual std::map<std::string, std::string> serialize() const{}
        virtual void unserialize(const std::map<std::string, std::string>& variables){}

        static constexpr Component::Type type()
        {
            return Component::Type::StaticRenderable;
        }
    protected:
    private:
};
}
#endif // CMP_STATICRENDERABLE_H
