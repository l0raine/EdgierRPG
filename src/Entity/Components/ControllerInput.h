#ifndef CMP_CONTROLLERINPUT_H
#define CMP_CONTROLLERINPUT_H

#include "Component.h"

namespace cmp
{
class ControllerInput : public Component
{
    public:
        /** Default constructor */
        ControllerInput(unsigned int i);
        /** Default destructor */
        virtual ~ControllerInput();

        virtual std::map<std::string, std::string> serialize() const{}
        virtual void unserialize(const std::map<std::string, std::string>& variables){}

        static constexpr Component::Type type()
        {
            return Component::Type::ControllerInput;
        }
    protected:
    private:
};
}
#endif // CMP_CONTROLLERINPUT_H
