#ifndef SYS_INVENTORY_H
#define SYS_INVENTORY_H

#include "System.h"
#include "Components/Inventory.h"

namespace sys
{
class Inventory : public System<cmp::Inventory>
{
    public:
        /** Default constructor */
        Inventory();
        /** Default destructor */
        virtual ~Inventory();

        virtual void update(float dt){}
    protected:
    private:
};
}
#endif // SYS_INVENTORY_H
