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
    //if(cameraView.getCenter().x > cameraView.getSize().x/2 || cameraView.getCenter().y > cameraView.getSize().y/2)

        cameraView.setCenter(EntityManager::getInstance()->getEntity(currentEntityID)->getPosition());
}

const sf::View& GameCamera::getCameraView()
{
    return cameraView;
}
