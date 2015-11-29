#ifndef CMP_ANIMATEDRENDERABLE_H
#define CMP_ANIMATEDRENDERABLE_H

#include "Component.h"

namespace cmp
{
class AnimatedRenderable : public Component
{
    public:
        /** Default constructor */
        AnimatedRenderable(unsigned int i);
        /** Default destructor */
        virtual ~AnimatedRenderable();

        virtual std::map<std::string, std::string> serialize() const{}
        virtual void unserialize(const std::map<std::string, std::string>& variables){}

        static constexpr Component::Type type()
        {
            return Component::Type::AnimatedRenderable;
        }
    protected:

    private:
};
}
#endif // CMP_ANIMATEDRENDERABLE_H
