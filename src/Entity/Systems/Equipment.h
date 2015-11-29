#ifndef SYS_EQUIPMENT_H
#define SYS_EQUIPMENT_H

#include "System.h"
#include "Components/Equipment.h"

namespace sys
{
class Equipment : public System<cmp::Equipment>
{
    public:
        /** Default constructor */
        Equipment();
        /** Default destructor */
        virtual ~Equipment();

        virtual void update(float dt){}
    protected:
    private:
};
}
#endif // SYS_EQUIPMENT_H
