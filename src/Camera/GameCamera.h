#ifndef GAMECAMERA_H
#define GAMECAMERA_H

#include <SFML/Graphics.hpp>
#include <memory>

class EntityBase;

class GameCamera
{
public:
    GameCamera();
    virtual ~GameCamera();
    static std::shared_ptr<GameCamera> getInstance();

    void setFocus(EntityBase* entity);
    const sf::View& getCameraView();
    void update();

protected:
private:
    unsigned int currentEntityID;
    sf::View cameraView;

    static std::shared_ptr<GameCamera> instance;
};

#endif // GAMECAMERA_H
