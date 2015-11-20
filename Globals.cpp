#include "Globals.h"

    //Variable definitions
    std::string texturePath = "./Files/Textures/";
    std::string soundPath = "./Files/";
    std::string fontPath = "./Files/Fonts/";
    std::string mapPath = "./Files/Maps/";
    sf::Vector2i windowSize(800,600);
    std::string guiFontPath = fontPath + "arial.ttf";
    std::string themePath = "./Files/Themes/";
    unsigned int mapLayerCount = 5;
    sf::RenderWindow* gameWindow;
    sf::Vector2u blankTilePosition = {96, 0};
