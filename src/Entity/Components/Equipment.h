#ifndef CMP_EQUIPMENT_H
#define CMP_EQUIPMENT_H

#include "Component.h"

namespace cmp
{
class Equipment : public Component
{
    public:
        /** Default constructor */
        Equipment(unsigned int i);
        /** Default destructor */
        virtual ~Equipment();

        virtual std::map<std::string, std::string> serialize() const{}
        virtual void unserialize(const std::map<std::string, std::string>& variables){}

        static constexpr Component::Type type()
        {
            return Component::Type::Equipment;
        }
    protected:
    private:
};
}
#endif // CMP_EQUIPMENT_H
