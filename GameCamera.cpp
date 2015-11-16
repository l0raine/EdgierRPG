#include "GameCamera.h"
#include "EntityManager.h"
#include "Globals.h"
#include "EntityBase.h"

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

}

const sf::View& GameCamera::getCameraView()
{
    return cameraView;
}
