#include "Player.h"

Player::Player()
{
    sf::Texture *text = ResourceManager::getInstance()->loadTexture("tilesheets/LX.png");

    sprite.addFrame(0, sf::IntRect(495,404,27,42));
    sprite.addFrame(0, sf::IntRect(522,404,23,42));
    sprite.addFrame(0, sf::IntRect(545,404,23,42));

    sprite.addFrame(1, sf::IntRect(495,447,28,41));
    sprite.addFrame(1, sf::IntRect(522,447,26,41));
    sprite.addFrame(1, sf::IntRect(546,447,26,41));

    sprite.addFrame(2, sf::IntRect(495,531,18,40));
    sprite.addFrame(2, sf::IntRect(513,530,20,40));
    sprite.addFrame(2, sf::IntRect(533,529,21,40));

    sprite.addFrame(3, sf::IntRect(495,489,18,40));
    sprite.addFrame(3, sf::IntRect(513,489,20,40));
    sprite.addFrame(3, sf::IntRect(533,489,21,40));


    sprite.addSpecialFrame(0, 0, sf::IntRect(572,447,28,41));
    sprite.addSpecialFrame(0, 0, sf::IntRect(600,447,26,41));
    sprite.addSpecialFrame(0, 0, sf::IntRect(625,447,26,41));

    setDirection(1);
    sprite.setFrameInterval(100);
    sprite.setTexture(text);
}

Player::~Player()
{
    //dtor
}
