#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <memory>

class EntityBase;
class EntityManager;
class MessageBase;

class EntityManager
{
    public:
        /** Default destructor */
        virtual ~EntityManager();

        static std::shared_ptr<EntityManager> getInstance();

        void draw(sf::RenderTarget &target, const sf::RenderStates &states);
        void registerEntity(std::unique_ptr<EntityBase> &entity); //Note: Takes ownership of object

        void handleMessage(std::unique_ptr<MessageBase> &message);

        void removeEntity(std::unique_ptr<EntityBase> &entity);
        void update();

        unsigned int getSelectedEntityID();
        EntityBase *getEntity(unsigned int entityID);
    protected:
    private:
        /** Default constructor */
        EntityManager();
        static std::shared_ptr<EntityManager> instance;

        std::vector<std::unique_ptr<EntityBase>> entities; //List of loaded entities
        unsigned int selectedEntityID;
        unsigned int entityCounter;

        sf::View cameraView;


};

#endif // ENTITYMANAGER_H
