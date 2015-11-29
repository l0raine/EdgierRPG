#ifndef CMP_TRADE_H
#define CMP_TRADE_H

#include "Component.h"

namespace cmp
{
class Trade : public Component
{
    public:
        /** Default constructor */
        Trade(unsigned int i);
        /** Default destructor */
        virtual ~Trade();

        virtual std::map<std::string, std::string> serialize() const{}
        virtual void unserialize(const std::map<std::string, std::string>& variables){}

        static constexpr Component::Type type()
        {
            return Component::Type::Trade;
        }
    protected:
    private:
};
}
#endif // CMP_TRADE_H
