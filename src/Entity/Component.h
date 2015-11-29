#ifndef COMPONENT_H
#define COMPONENT_H

#include <map>
#include <string>

class Component
{
public:
    enum class Type : std::size_t
    {
        None = 0,
        StaticRenderable = 1,
        AnimatedRenderable = 2,
        ControllerInput = 3,
        Inventory = 4,
        SkillTree = 5,
        Equipment = 6,
        Physics = 7,
        Quest = 8,
        Combat = 9,
        CombatAI = 10,
        PathfindingAI = 11,
        Trade = 12,
        Interactable = 13,
        Scriptable = 14,

        MAX = 15,
    };

    Component(unsigned int i);
    virtual ~Component() = default;

    unsigned int ID() const;

    // must be implemented
    static constexpr Type type();

    static constexpr Type type(const char* str);
    static constexpr const char* type(Component::Type en);

    virtual std::map<std::string, std::string> serialize() const = 0;
    virtual void unserialize(const std::map<std::string, std::string>& variables) = 0;

private:
    unsigned int id;

    static constexpr std::pair<const char*, Type> TypeStrings[] =
    {
        {"None", Type::None},
        {"StaticRenderable", Type::StaticRenderable},
        {"AnimatedRenderable", Type::AnimatedRenderable},
        {"ControllerInput", Type::ControllerInput},
        {"Inventory", Type::Inventory},
        {"SkillTree", Type::SkillTree},
        {"Equipment", Type::Equipment},
        {"Physics", Type::Physics},
        {"Quest", Type::Quest},
        {"Combat", Type::Combat},
        {"CombatAI", Type::CombatAI},
        {"PathfindingAI", Type::PathfindingAI},
        {"Trade", Type::Trade},
        {"Interactable", Type::Interactable},
        {"Scriptable", Type::Scriptable},
    };
};


namespace
{
constexpr bool isSame(const char* x, const char* y)
{
    return !*x && !*y ? true : (*x == *y && isSame(x + 1, y + 1));
}
}

constexpr Component::Type Component::type(const char* str)
{
    constexpr std::size_t MAX = static_cast<std::size_t>(Type::MAX);

    for(std::size_t i = 1; i < MAX; i++)
    {
        if(isSame(str, TypeStrings[i].first))
        {
            return TypeStrings[i].second;
        }
    }

    return Type::None;
}

constexpr const char* Component::type(Component::Type en)
{
    constexpr std::size_t MAX = static_cast<std::size_t>(Type::MAX);

    std::size_t i = static_cast<std::size_t>(en);

    if(i < MAX)
    {
        return TypeStrings[i].first;
    }

    return "None";
}

namespace std
{
	template<>
	struct hash<Component::Type>
	{
		std::size_t operator()(const Component::Type& t) const
		{
			return std::hash<std::underlying_type<Component::Type>::type>()(static_cast<std::underlying_type<Component::Type>::type>(t));
		}
	};
}

#endif // COMPONENT_H
