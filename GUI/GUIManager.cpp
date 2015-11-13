#include "GUIManager.h"
#include "FRDGUI.h"

GUIManager::GUIManager(sf::Vector2i &windowSize, const std::string &fontFilePath, const sf::Color &defaultFontColour, unsigned int defaultFontSize)
{
    gui = new frd::FRDGUI(windowSize, fontFilePath, defaultFontColour, defaultFontSize);
}

GUIManager* GUIManager::getInstance()
{
    if(instance == nullptr)
    {
        instance = new GUIManager(gl::windowSize, gl::fontPath, sf::Color::Yellow, 15);
    }
    return instance;
}

GUIManager::~GUIManager()
{
    delete gui;
}

frd::FRDGUI* GUIManager::getFRDGUIHandle()
{
    return gui;
}
