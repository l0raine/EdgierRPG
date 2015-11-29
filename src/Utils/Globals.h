#ifndef GLOBALS_H
#define GLOBALS_H

#include<SFML/Graphics.hpp>

//Forward global variable declarations
extern sf::Vector2i windowSize;
extern std::string texturePath;
extern std::string soundPath;
extern std::string musicPath;
extern std::string fontPath;
extern std::string guiFontPath;
extern std::string mapPath;
extern std::string themePath;
extern unsigned int mapLayerCount;
extern sf::RenderWindow* gameWindow;
extern sf::Vector2u blankTilePosition;


#endif // GLOBALS_H
