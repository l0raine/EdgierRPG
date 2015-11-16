#include "GameCamera.h"
#include "EntityManager.h"
#include "Globals.h"
#include "EntityBase.h"
#include "MapManager.h"
#include "Map.h"

std::shared_ptr<GameCamera> GameCamera::instance;

GameCamera::GameCamera()
{
    //ctor
    cameraView = sf::View(sf::Vector2f(windowSize.x/2, windowSize.y/2), sf::Vector2f(windowSize.x, windowSize.y));
}

GameCamera::~GameCamera()
{
    //dtor
}

std::shared_ptr<GameCamera> GameCamera::getInstance()
{
    if(instance == nullptr)
    {
        instance = std::shared_ptr<GameCamera>(new GameCamera);
    }
    return instance;
}

void GameCamera::setFocus(EntityBase* entity)
{
    currentEntityID = entity->getEntityID();
}

void GameCamera::update()
{
    float posX, posY;
    const sf::Vector2f &unitPos = EntityManager::getInstance()->getEntity(EntityManager::getInstance()->getSelectedEntityID())->getPosition();
    sf::Vector2i mapSize = MapManager::getInstance()->getCurrentMap()->getMapSizePixels();

    if( unitPos.x > windowSize.x / 2)
        posX = unitPos.x;
    else
        posX = windowSize.x / 2;

    if(unitPos.y > windowSize.y / 2)
        posY = unitPos.y;
    else
        posY = windowSize.y / 2;

    if (posX + windowSize.x / 2 > mapSize.x)
    	posX = float(mapSize.x - windowSize.x / 2);

    if (posY + windowSize.y / 2 > mapSize.y )
    	posY = float(mapSize.y - windowSize.y / 2);

    cameraView.setCenter(posX, posY);
}

const sf::View& GameCamera::getCameraView()
{
    return cameraView;
}
