#include "GameCamera.h"
#include "EntityManager.h"

GameCamera::GameCamera()
{
    //ctor
    cameraView = sf::View(sf::Vector2f(windowSize.x/2, windowSize.y/2), sf::Vector2f(windowSize.x, windowSize.y));
}

GameCamera::~GameCamera()
{
    //dtor
}

void GameCamera::setFocus(EntityBase* entity)
{
    currentEntityID = entity->getEntityID();
}

void GameCamera::update()
{
    sf::Vector2f position;

    position.x = EntityManager::getInstance()->getEntity(EntityManager::getInstance()->getSelectedEntityID())->getPosition().x - (cameraView.getSize().x / 2);
    position.y = EntityManager::getInstance()->getEntity(EntityManager::getInstance()->getSelectedEntityID())->getPosition().y - (cameraView.getSize().x / 2);

    if(position.x < 0)
        position.x = 0;
    if(position.y < 0)
        position.y = 0;


    cameraView.reset(sf::FloatRect(position.x, position.y, cameraView.getSize().x, cameraView.getSize().y));
}

const sf::View& GameCamera::getCameraView()
{
    return cameraView;
}
