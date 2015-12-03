#ifndef SYSTEM_MAP_H
#define SYSTEM_MAP_H

#include <unordered_map>

#include "Component.h"
#include "System.h"

class SystemMap
{
    private:
        using Map = std::unordered_map<Component::Type, BaseSystem*>;

    public:
        template<typename T, typename std::enable_if<std::is_base_of<Component, T>::value>::type* = nullptr>
        System<T>* get()
        {
            if(systems.find(T::type()) != systems.end())
            {
                return static_cast<System<T>*>(systems[T::type()]);
            }
            else
            {
                return nullptr;
            }
        }

        BaseSystem* get(Component::Type t)
        {
            if(systems.find(t) != systems.end())
            {
                return systems[t];
            }
            else
            {
                return nullptr;
            }
        }

        void add(BaseSystem* sys)
        {
            systems[sys->typeEnum()] = sys;
        }

        void handleMessage(std::unique_ptr<MessageBase> message)
        {
            for(Map::iterator iter = systems.begin(); iter != systems.end(); iter++)
            {
                iter->second->handleMessage(std::move(message));
            }
        }

        // forward iterator requests to the AssocMap
        Map::iterator begin()
        {
            return systems.begin();
        }

        Map::const_iterator begin() const
        {
            return systems.begin();
        }

        Map::iterator end()
        {
            return systems.end();
        }

        Map::const_iterator end() const
        {
            return systems.end();
        }

    private:
        Map systems;
};

#endif	// SYSTEM_MAP_H
