#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>

#include "MessageBase.h"
#include "EntityBase.h"
#include "Events/KeyEvent.h"
#include "InputHandler.h"

class EntityManager
{
    public:
        /** Default destructor */
        virtual ~EntityManager();

        static std::shared_ptr<EntityManager> getInstance();

        void draw(sf::RenderTarget &target, const sf::RenderStates &states);
        void registerEntity(std::unique_ptr<EntityBase> &entity); //Note: Takes ownership of object

        void handleMessage(std::unique_ptr<MessageBase> &message);


        //TODO
        void removeEntity(std::unique_ptr<EntityBase> &entity);
        void update();
    protected:
    private:
        /** Default constructor */
        EntityManager();
        static std::shared_ptr<EntityManager> instance;

        std::vector<std::unique_ptr<EntityBase>> entities; //List of loaded entities
        unsigned int selectedEntityID;


};

#endif // ENTITYMANAGER_H
