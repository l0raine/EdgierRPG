#ifndef SYS_TRADE_H
#define SYS_TRADE_H

#include "System.h"
#include "Components/Trade.h"

namespace sys
{
class Trade : public System<cmp::Trade>
{
    public:
        /** Default constructor */
        Trade();
        /** Default destructor */
        virtual ~Trade();

        virtual void update(float dt){}
    protected:
    private:
};
}
#endif // SYS_TRADE_H
