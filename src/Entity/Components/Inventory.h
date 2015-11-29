#ifndef CMP_INVENTORY_H
#define CMP_INVENTORY_H

#include "Component.h"

namespace cmp
{
class Inventory : public Component
{
    public:
        /** Default constructor */
        Inventory(unsigned int i);
        /** Default destructor */
        virtual ~Inventory();

        virtual std::map<std::string, std::string> serialize() const{}
        virtual void unserialize(const std::map<std::string, std::string>& variables){}

        static constexpr Component::Type type()
        {
            return Component::Type::Inventory;
        }
    protected:
    private:
};
}
#endif // CMP_INVENTORY_H
