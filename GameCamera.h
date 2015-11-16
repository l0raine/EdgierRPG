#ifndef GAMECAMERA_H
#define GAMECAMERA_H

#include<SFML/Graphics.hpp>
#include "EntityBase.h"


class GameCamera
{
    public:
        GameCamera();
        virtual ~GameCamera();


        void setFocus(EntityBase* entity);
        const sf::View& getCameraView();
        void update();

    protected:
    private:
        unsigned int currentEntityID;
        sf::View cameraView;
};

#endif // GAMECAMERA_H
