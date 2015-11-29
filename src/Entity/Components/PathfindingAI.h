#ifndef CMP_PATHFINDINGAI_H
#define CMP_PATHFINDINGAI_H

#include "Component.h"

namespace cmp
{
class PathfindingAI : public Component
{
    public:
        /** Default constructor */
        PathfindingAI(unsigned int i);
        /** Default destructor */
        virtual ~PathfindingAI();

        virtual std::map<std::string, std::string> serialize() const{}
        virtual void unserialize(const std::map<std::string, std::string>& variables){}

        static constexpr Component::Type type()
        {
            return Component::Type::PathfindingAI;
        }
    protected:
    private:
};
}
#endif // CMP_PATHFINDINGAI_H
