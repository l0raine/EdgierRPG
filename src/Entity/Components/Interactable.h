#ifndef CMP_INTERACTABLE_H
#define CMP_INTERACTABLE_H

#include "Component.h"

namespace cmp
{
class Interactable : public Component
{
    public:
        /** Default constructor */
        Interactable(unsigned int i);
        /** Default destructor */
        virtual ~Interactable();

        virtual std::map<std::string, std::string> serialize() const{}
        virtual void unserialize(const std::map<std::string, std::string>& variables){}

        static constexpr Component::Type type()
        {
            return Component::Type::Interactable;
        }
    protected:
    private:
};
}
#endif // CMP_INTERACTABLE_H
